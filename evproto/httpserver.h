// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_HTTPSERVER_H
#define EVPROTO_HTTPSERVER_H

#include "evproto/common.h"

#include <google/protobuf/service.h>

#include <stdint.h>

struct evhttp;
struct evhttp_request;
struct evhttp_bound_socket;

namespace evproto
{

class EventLoop;

class HttpServer
{
 public:
  HttpServer(EventLoop* loop, uint16_t port);
  ~HttpServer();
  void stop();
  struct evhttp* evHttp();

 private:
  void requestCallback(struct evhttp_request*);
  static void requestCallback(struct evhttp_request*, void*);

  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(HttpServer);
  EventLoop* loop_;
  struct evhttp* const evhttp_;
  struct evhttp_bound_socket* boundSocket_;
};

}

#endif  // EVPROTO_EVENTLOOP_H

