#include <iostream>
#include <packio/packio.h>

using packio::arg;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::rpc;

int main(int, char **)
{
   using namespace packio::arg_literals;

   // Declare a server and a client, sharing the same io_context
   packio::net::io_context        io;
   packio::net::ip::tcp::endpoint server_ep{packio::net::ip::make_address("127.0.0.1"), 4000};
   auto                           client = make_client(packio::net::ip::tcp::socket{io});

   // Connect the client
   client->socket().connect(server_ep);

   // Make an asynchronous call with named arguments
   client->async_call("add", std::tuple{arg("a") = 42, arg("b") = 24}, [&](packio::error_code, const rpc::response_type &r) {
      std::cout << "42 + 24 = " << r.result.get<int>() << std::endl;
   });

   // Use packio::net::use_future with named arguments and literals
   client->async_call("multiply", std::tuple{"a"_arg = 12, "b"_arg = 23},
                      [&](packio::error_code, const rpc::response_type &r) {
                         std::cout << "12 * 23 = " << r.result.get<int>() << std::endl;
                      });

   io.run();

   return 0;
}