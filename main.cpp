#include <iostream>
#include <packio/packio.h>

using packio::arg;
using packio::nl_json_rpc::completion_handler;
using packio::nl_json_rpc::make_client;
using packio::nl_json_rpc::make_server;
using packio::nl_json_rpc::rpc;

int main(int, char **)
{
   using namespace packio::arg_literals;

   // Declare a server and a client, sharing the same io_context
   packio::net::io_context        io;
   packio::net::ip::tcp::endpoint bind_ep{packio::net::ip::make_address("127.0.0.1"), 0};
   auto                           server = make_server(packio::net::ip::tcp::acceptor{io, bind_ep});
   auto                           client = make_client(packio::net::ip::tcp::socket{io});

   // Declare a synchronous callback with named arguments
   server->dispatcher()->add("add", {"a", "b"}, [](int a, int b) { return a + b; });
   // Declare an asynchronous callback with named arguments
   server->dispatcher()->add_async("multiply", {"a", "b"}, [&io](completion_handler complete, int a, int b) {
      // Call the completion handler later
      packio::net::post(io, [a, b, complete = std::move(complete)]() mutable { complete(a * b); });
   });

   // Connect the client
   client->socket().connect(server->acceptor().local_endpoint());
   // Accept connections
   server->async_serve_forever();
   // Run the io_context
   std::thread thread{[&] { io.run(); }};

   // Make an asynchronous call with named arguments
   std::promise<int> add1_result, multiply_result;
   client->async_call("add", std::tuple{arg("a") = 42, arg("b") = 24},
                      [&](packio::error_code, const rpc::response_type &r) { add1_result.set_value(r.result.get<int>()); });
   std::cout << "42 + 24 = " << add1_result.get_future().get() << std::endl;

   // Use packio::net::use_future with named arguments and literals
   auto add_future = client->async_call("multiply", std::tuple{"a"_arg = 12, "b"_arg = 23}, packio::net::use_future);
   std::cout << "12 * 23 = " << add_future.get().result.get<int>() << std::endl;

   io.stop();
   thread.join();

   return 0;
}