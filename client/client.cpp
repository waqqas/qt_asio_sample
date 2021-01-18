#include "mainwindow.h"

#include <QApplication>
#include <packio/packio.h>
#include <thread>

using packio::arg;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::rpc;

int main(int argc, char *argv[])
{

   using namespace packio::arg_literals;

   // Declare a server and a client, sharing the same io_context
   packio::net::io_context                                       io;
   boost::asio::executor_work_guard<decltype(io.get_executor())> work{io.get_executor()};

   packio::net::ip::tcp::endpoint server_ep{packio::net::ip::make_address("127.0.0.1"), 4000};
   auto                           client = make_client(packio::net::ip::tcp::socket{io});

   // Connect the client
   client->socket().connect(server_ep);

   // Run the io_context
   std::thread thread{[&] { io.run(); }};

   // Qt application initialization
   QApplication q(argc, argv);
   MainWindow   w(client);

   w.show();

   int return_code = q.exec();

   thread.join();

   return return_code;
}