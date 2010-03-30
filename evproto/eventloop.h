// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_EVENTLOOP_H
#define EVPROTO_EVENTLOOP_H

#include "evproto/common.h"

struct event_base;

namespace evproto
{

class EventLoop
{
 public:
  EventLoop();
  ~EventLoop();
  int loop();
  struct event_base* eventBase();
 private:
  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(EventLoop);
  struct event_base* const base_;
};

}

#endif  // EVPROTO_EVENTLOOP_H
