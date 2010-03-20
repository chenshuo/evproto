// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/rpcchannel.h"

#include <iostream>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <event2/event.h>

using namespace std;

namespace evproto
{

RpcChannel::RpcChannel()
{
}

RpcChannel::~RpcChannel()
{
}

void RpcChannel::CallMethod(const gpb::MethodDescriptor* method,
                          gpb::RpcController* controller,
                          const gpb::Message* request,
                          gpb::Message* response,
                          gpb::Closure* done)
{
  cout << method->name() << endl;
  cout << method->full_name() << endl;
}

}

