// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/httpserver.h"
#include "evproto/eventloop.h"

#include <glog/logging.h>

#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/http_struct.h>

namespace evproto
{

HttpServer::HttpServer(EventLoop* loop, uint16_t port)
  : loop_(loop),
    http_(CHECK_NOTNULL(
          ::evhttp_new(loop->eventBase()))),
    boundSocket_(CHECK_NOTNULL(
          ::evhttp_bind_socket_with_handle(http_, "0.0.0.0", port)))
{
  // CHECK_EQ(::evhttp_set_cb(http_, "/hello", requestCallback, this), 0);
  // libevent lookup uri by linear searching,
  // so we provide general callback only.
  ::evhttp_set_gencb(http_, requestCallback, 0);
}

HttpServer::~HttpServer()
{
  ::evhttp_free(http_);
}

void HttpServer::stop()
{
  ::evhttp_del_accept_socket(http_, boundSocket_);
}

void HttpServer::requestCallback(struct evhttp_request* req)
{
  const char* uri = req->uri;
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

