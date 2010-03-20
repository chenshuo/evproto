#include "evproto/evproto.h"
#include "evproto/eventloop.h"
#include "evproto/httpserver.h"

#include <glog/logging.h>

int main(int argc, char* argv[])
{
  evproto::initialize(argc, argv);

  evproto::EventLoop loop;
  evproto::HttpServer httpserver(&loop, 2000);

  int ret = loop.loop();
  LOG(INFO) << "EventLoop::loop() returns " << ret;
}
