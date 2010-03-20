// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/eventloop.h"

#include <glog/logging.h>

#include <event2/event.h>

namespace evproto
{

EventLoop::EventLoop()
  : base_(CHECK_NOTNULL(::event_base_new()))
{
  LOG(INFO) << "Using Libevent with backend method "
            << ::event_base_get_method(base_);
}

EventLoop::~EventLoop()
{
  ::event_base_free(base_);
}

int EventLoop::loop()
{
  return ::event_base_loop(base_, 0);
}

struct event_base* EventLoop::eventBase()
{
  return base_;
}

}
