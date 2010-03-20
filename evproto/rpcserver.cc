// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/rpcserver.h"
#include "evproto/rpccontroller.h"
#include "evproto/httpserver.h"

#include <iostream>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <event2/event.h>
#include <event2/rpc.h>

using namespace std;

namespace evproto
{

RpcServer::RpcServer(HttpServer* http)
  : http_(http),
    rpcbase_((CHECK_NOTNULL(::evrpc_init(http_->evHttp()))))
{
}

RpcServer::~RpcServer()
{
  ::evrpc_free(rpcbase_);
}

void RpcServer::invokeCallback(struct evrpc_req_generic*, void*)
{
}

bool RpcServer::registerService(gpb::Service* service)
{
  const gpb::ServiceDescriptor* desc = service->GetDescriptor();
  LOG(INFO) << "registering service" << desc->full_name();
  
  bool succeed = true;
  int methodCount = desc->method_count();
  void *(*req_new)(void) = 0;
  void (*req_free)(void *) = 0;
  void *(*resp_new)(void) = 0;
  void (*resp_free)(void *) = 0;
  int (*resp_complete)(void *) = 0;
  for (int i = 0; i < methodCount; ++i)
  {
    const gpb::MethodDescriptor* method = desc->method(i);
    LOG(INFO) << "registering rpc call " << method->full_name();
    int ret = evrpc_register_generic(
        rpcbase_,
        method->full_name().c_str(),
        &RpcServer::invokeCallback,
        const_cast<gpb::MethodDescriptor*>(method),
        req_new,
        req_free,
        &RpcController::unmarshal,
        resp_new,
        resp_free,
        resp_complete,
        &RpcController::marshal);

    if (ret)
    {
      succeed = false;
    }
  }
  return succeed;
}

}
