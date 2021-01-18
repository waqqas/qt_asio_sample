#include <packio/packio.h>

using packio::nl_json_rpc::completion_handler;
using packio::nl_json_rpc::make_server;
using packio::nl_json_rpc::rpc;

int main(int, char **)
{
   // Declare a server and a client, sharing the same io_context
   packio::net::io_context        io;
   packio::net::ip::tcp::endpoint bind_ep{packio::net::ip::make_address("127.0.0.1"), 4000};
   auto                           server = make_server(packio::net::ip::tcp::acceptor{io, bind_ep});

   // Declare a synchronous callback with named arguments
   server->dispatcher()->add("add", {"a", "b"}, [](int a, int b) { return a + b; });
   
   // Declare an asynchronous callback with named arguments
   server->dispatcher()->add_async("multiply", {"a", "b"}, [&io](completion_handler complete, int a, int b) {
      // Call the completion handler later
      packio::net::post(io, [a, b, complete = std::move(complete)]() mutable { complete(a * b); });
   });

   // Accept connections
   server->async_serve_forever();
   // Run the io_context
   io.run();

   return 0;
}