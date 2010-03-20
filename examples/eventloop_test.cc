#include "evproto/evproto.h"
#include "evproto/eventloop.h"

#include <glog/logging.h>

int main(int argc, char* argv[])
{
  evproto::initialize(argc, argv);

  evproto::EventLoop loop;
  

  int ret = loop.loop();
  LOG(INFO) << "EventLoop::loop() returns " << ret;
}
