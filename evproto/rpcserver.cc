// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/rpcserver.h"

#include <iostream>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <event2/event.h>

using namespace std;

namespace evproto
{

RpcServer::RpcServer(HttpServer* http)
  : http_(http)
{
}

RpcServer::~RpcServer()
{
}

void RpcServer::registerService(gpb::Service* service)
{
  const gpb::ServiceDescriptor* desc = service->GetDescriptor();
  LOG(INFO) << "registering " << desc->full_name();
}

}
