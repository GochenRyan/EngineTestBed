#include "rpc_service.hpp"
#include <coro_rpc/coro_rpc_server.hpp>

using namespace coro_rpc;

int main() {
   coro_rpc_server server(/*thread_num =*/10, /*port =*/9000);
   server.register_handler<echo>(); // register function echo
   server.start(); // start the server & block
  return 0;
}