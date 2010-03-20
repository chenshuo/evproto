// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_RPCSERVER_H
#define EVPROTO_RPCSERVER_H

#include "evproto/common.h"

#include <google/protobuf/service.h>

struct evhttp_connection;
struct evrpc_base;
struct evrpc_req_generic;

namespace evproto
{

class HttpServer;

class RpcServer
{
 public:
  RpcServer(HttpServer*);
  ~RpcServer();
  bool registerService(gpb::Service* service);
  void CallMethod(const gpb::MethodDescriptor* method,
                  gpb::RpcController* controller,
                  const gpb::Message* request,
                  gpb::Message* response,
                  gpb::Closure* done);
 private:
  static void invokeCallback(struct evrpc_req_generic*, void*);
  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(RpcServer);
  HttpServer* http_;
  struct evrpc_base* rpcbase_;
};

}

#endif  // EVPROTO_RPCSERVER_H

