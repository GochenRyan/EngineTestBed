#include "rpc_service.hpp"
#include <coro_rpc/coro_rpc_client.hpp>

using namespace coro_rpc;
using namespace async_simple::coro;

Lazy<void> test_client() {
  coro_rpc_client client;
  co_await client.connect("localhost", /*port =*/"9000"); // connect to the server

  auto r = co_await client.call<echo>("hello coro_rpc"); // call remote function echo
  if (!r) {
    std::cout << "err: " << r.error().msg << std::endl;
  }
  else
  {
    std::cout << r.value() << "\n"; //will print "hello coro_rpc"
  }
}

int main() {
  syncAwait(test_client());
}