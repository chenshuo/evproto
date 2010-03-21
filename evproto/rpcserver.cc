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
//#include <event2/rpc_struct.h>

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

void RpcServer::invokeCallback(struct evrpc_req_generic* req, void*)
{
  //evbuffer_add(req->rpc_data, "hello", 5);
  evrpc_request_done(req);
}

bool RpcServer::registerService(gpb::Service* service)
{
  const gpb::ServiceDescriptor* desc = service->GetDescriptor();
  LOG(INFO) << "registering service" << desc->full_name();
  
  bool succeed = true;
  int methodCount = desc->method_count();
  for (int i = 0; i < methodCount; ++i)
  {
    const gpb::MethodDescriptor* method = desc->method(i);
    LOG(INFO) << "registering rpc call " << method->full_name();
    int ret = evrpc_register_generic(
        rpcbase_,
        method->full_name().c_str(),
        &RpcServer::invokeCallback,
        const_cast<gpb::MethodDescriptor*>(method),
        &RpcController::newMessage,
        const_cast<gpb::Message*>(&service->GetRequestPrototype(method)),
        &RpcController::deleteMessage,
        &RpcController::unmarshal,
        &RpcController::newMessage,
        const_cast<gpb::Message*>(&service->GetResponsePrototype(method)),
        &RpcController::deleteMessage,
        &RpcController::complete,
        &RpcController::marshal);

    if (ret)
    {
      succeed = false;
    }
  }
  return succeed;
}

}
