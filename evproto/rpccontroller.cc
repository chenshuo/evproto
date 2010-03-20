// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/rpccontroller.h"

#include <glog/logging.h>
#include <google/protobuf/message.h>

#include <sys/queue.h>
#include <event2/buffer.h>
//#include <event2/event.h>
//#include <event2/rpc.h>
#include <event2/rpc_struct.h>

namespace evproto
{

RpcController::RpcController()
{
}

RpcController::~RpcController()
{
}

void RpcController::statusCallback(
      struct evrpc_status *status,
      void* request,
      void* response,
      void *arg)
{
  VLOG(0) << "statusCallback " << status->error;
}

void RpcController::marshal(struct evbuffer* buf, void* arg)
{
  gpb::Message* msg = static_cast<gpb::Message*>(arg);
  VLOG(0) << "marshal " << msg->GetTypeName();
  std::string s = msg->SerializeAsString();
  evbuffer_add(buf, s.data(), s.size());
}

void RpcController::clear(void* arg)
{
  gpb::Message* msg = static_cast<gpb::Message*>(arg);
  VLOG(0) << "clear " << msg->GetTypeName();
}

int RpcController::unmarshal(void* arg, struct evbuffer*)
{
  gpb::Message* msg = static_cast<gpb::Message*>(arg);
  VLOG(0) << "unmarshal " << msg->GetTypeName();
  return 0;
}

}
