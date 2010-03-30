// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/httpserver.h"
#include "evproto/eventloop.h"

#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/http_struct.h>

namespace evproto
{

HttpServer::HttpServer(EventLoop* loop, uint16_t port)
  : loop_(loop),
    evhttp_(CHECK_NOTNULL(
          ::evhttp_new(loop->eventBase()))),
    boundSocket_(CHECK_NOTNULL(
          ::evhttp_bind_socket_with_handle(evhttp_, "0.0.0.0", port)))
{
  // CHECK_EQ(::evhttp_set_cb(http_, "/hello", requestCallback, this), 0);
  // libevent lookup uri by linear searching,
  // so we provide general callback only.
  ::evhttp_set_gencb(evhttp_, requestCallback, 0);
}

HttpServer::~HttpServer()
{
  ::evhttp_free(evhttp_);
}

void HttpServer::stop()
{
  ::evhttp_del_accept_socket(evhttp_, boundSocket_);
}

struct evhttp* HttpServer::evHttp()
{
  return evhttp_;
}

void HttpServer::requestCallback(struct evhttp_request* req)
{
  const char* uri = req->uri;
  if (req->type == EVHTTP_REQ_POST)
  {
  }
  else
  {
  }
  LOG(INFO) << "get " << uri;
  struct evbuffer *evb = evbuffer_new();
  evbuffer_add(evb, "hello\r\n", 7);
  ::evhttp_send_reply(req, HTTP_OK, "OK", evb);
  evbuffer_free(evb);
}

void HttpServer::requestCallback(struct evhttp_request* req, void* obj)
{
  static_cast<HttpServer*>(obj)->requestCallback(req);
}

}

