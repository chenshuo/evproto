// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_RPCCHANNEL_H
#define EVPROTO_RPCCHANNEL_H

#include "evproto/common.h"

#include <google/protobuf/service.h>

struct event_base;

namespace evproto {

class RpcChannel : public gpb::RpcChannel
{
 public:
  RpcChannel();
  virtual ~RpcChannel();
  virtual void CallMethod(const gpb::MethodDescriptor* method,
                          gpb::RpcController* controller,
                          const gpb::Message* request,
                          gpb::Message* response,
                          gpb::Closure* done);
 private:
  EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(RpcChannel);
};

}

#endif  // EVPROTO_RPCCHANNEL_H
