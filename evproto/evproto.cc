// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "evproto/evproto.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/message.h>

#include <event2/event.h>
#include <event2/thread.h>

#if !defined(LIBEVENT_VERSION_NUMBER) || LIBEVENT_VERSION_NUMBER < 0x02000400
#error "This version of Libevent is not supported; Get 2.0.4-alpha or later."
#endif

namespace evproto
{

namespace internal
{

void eventLogToGlog(int severity, const char *msg)
{
  switch (severity) {
    case _EVENT_LOG_DEBUG:
      VLOG(1) << msg;
      break;
    case _EVENT_LOG_MSG:
      LOG(INFO) << msg;
      break;
    case _EVENT_LOG_WARN:
      LOG(WARNING) << msg;
      break;
    case _EVENT_LOG_ERR:
      LOG(ERROR) << msg;
      break;
    default:
      LOG(ERROR) << msg;
      break;
  }
}

void protobufLogHandler(google::protobuf::LogLevel level, const char* filename, int line,
                        const std::string& message)
{
  google::LogMessage(filename, line, level).stream() << message;
}

void eventFatal(int err)
{
  LOG(FATAL) << "libevent2 fatal " << err;
}

} // namespace internal

// TODO: pass back modified argc and argv.
void initialize(int argc, char* argv[])
{
  google::InitGoogleLogging(argv[0]);
  ::event_set_log_callback(internal::eventLogToGlog);
  google::protobuf::SetLogHandler(internal::protobufLogHandler);

#if EVTHREAD_USE_WINDOWS_THREADS_IMPLEMENTED
  CHECK_EQ(::evthread_use_windows_threads(), 0);
#elif EVTHREAD_USE_PTHREADS_IMPLEMENTED
  CHECK_EQ(::evthread_use_pthreads(), 0);
#endif

#ifndef NDEBUG
  // ::evthread_enable_lock_debuging();
  // ::event_enable_debug_mode();
#endif

  CHECK_EQ(LIBEVENT_VERSION_NUMBER, ::event_get_version_number())
    << "libevent2 version number mismatch";
  google::ParseCommandLineFlags(&argc, &argv, true);
  LOG(INFO) << argv[0] << " initialized";
}

}

