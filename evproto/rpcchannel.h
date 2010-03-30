// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_RPCCHANNEL_H
#define EVPROTO_RPCCHANNEL_H

#include "evproto/common.h"

#include <vector>

#include <google/protobuf/service.h>

struct evhttp_connection;
struct evrpc_pool;
struct evrpc_status;

namespace evproto
{

class EventLoop;

// TODO allow async DNS resolving
class RpcChannel : public gpb::RpcChannel
{
 public:
  RpcChannel(EventLoop* loop);
  bool addServer(const char* host, uint16_t port);
  virtual ~RpcChannel();
  virtual void CallMethod(const gpb::MethodDescriptor* method,
                          gpb::RpcController* controller,
                          const gpb::Message* request,
                          gpb::Message* response,
                          gpb::Closure* done);
 private:
  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(RpcChannel);
  EventLoop* const loop_;
  struct evrpc_pool* const pool_;
  std::vector<struct evhttp_connection*> addedConns_;
};

}

#endif  // EVPROTO_RPCCHANNEL_H
