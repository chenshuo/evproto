// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_RPCSERVER_H
#define EVPROTO_RPCSERVER_H

#include "evproto/common.h"

#include <google/protobuf/service.h>

struct event_base;

namespace evproto
{

class HttpServer;

class RpcServer
{
 public:
  RpcServer(HttpServer*);
  ~RpcServer();
  void registerService(gpb::Service* service);
  void CallMethod(const gpb::MethodDescriptor* method,
                  gpb::RpcController* controller,
                  const gpb::Message* request,
                  gpb::Message* response,
                  gpb::Closure* done);
 private:
  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(RpcServer);
  HttpServer* http_;
};

}

#endif  // EVPROTO_RPCSERVER_H

