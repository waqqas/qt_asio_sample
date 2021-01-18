#include "mainwindow.h"

int main(int argc, char *argv[])
{
   MyClient myClient;

   myClient.client->socket().connect(myClient.server_ep);
   
   myClient.client->async_call("add", std::tuple{arg("a") = 24, arg("b") = 42},
                         [&](packio::error_code, const rpc::response_type &r) {
                            std::cout << 24 << " * " << 42 << " = " << r.result.get<int>() << std::endl;
                           //  result = r.result.get<int>();
                         });

   // Run the io_context
   std::thread thread{[&] { myClient.io.run(); }};

   // Qt application initializatin
   QApplication q(argc, argv);
   MainWindow   w(&myClient);

   w.show();

   int return_code = q.exec();

   thread.join();

   return return_code;
}