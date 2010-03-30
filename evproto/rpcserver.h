// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_RPCSERVER_H
#define EVPROTO_RPCSERVER_H

#include "evproto/common.h"

#include <vector>
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

 private:
  static void invokeCallback(struct evrpc_req_generic*, void*);
  static void doneCallback(struct evrpc_req_generic*);
  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(RpcServer);
  HttpServer* http_;
  struct evrpc_base* rpcbase_;
  struct RpcMethod
  {
    gpb::Service* service;
    const gpb::MethodDescriptor* method;
  };
  std::vector<RpcMethod*> toDelete_;
};

}

#endif  // EVPROTO_RPCSERVER_H

