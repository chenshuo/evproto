// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/rpcchannel.h"
#include "evproto/rpccontroller.h"
#include "evproto/eventloop.h"

#include <iostream>
#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/rpc.h>

using namespace std;

namespace evproto
{

RpcChannel::RpcChannel(EventLoop* loop)
  : loop_(loop),
    pool_(CHECK_NOTNULL(::evrpc_pool_new(loop->eventBase())))
{
}

RpcChannel::~RpcChannel()
{
  for (size_t i = 0; i < addedConns_.size(); ++i)
  {
    ::evrpc_pool_remove_connection(pool_, addedConns_[i]);
    ::evhttp_connection_free(addedConns_[i]);
  }

  ::evrpc_pool_free(pool_);
}

bool RpcChannel::addServer(const char* host, uint16_t port)
{
  struct evhttp_connection* evcon = ::evhttp_connection_base_new(
      NULL, NULL, host, port);
  if (evcon)
  {
    ::evrpc_pool_add_connection(pool_, evcon);
    addedConns_.push_back(evcon);
  }
  return evcon != NULL;
}

void RpcChannel::CallMethod(const gpb::MethodDescriptor* method,
                          gpb::RpcController* controller,
                          const gpb::Message* request,
                          gpb::Message* response,
                          gpb::Closure* done)
{
  cout << method->name() << endl;
  cout << method->full_name() << endl;
  ::evrpc_send_request_generic(
      pool_,
      const_cast<gpb::Message*>(request),
      response,
      &RpcController::statusCallback,
      controller,
      method->full_name().c_str(),
      &RpcController::marshal,
      &RpcController::clear,
      &RpcController::unmarshal);
}

}

