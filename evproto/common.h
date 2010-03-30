// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/evproto/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#ifndef EVPROTO_COMMON_H
#define EVPROTO_COMMON_H

#define EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                            \
  void operator=(const TypeName&)

namespace google
{
namespace protobuf
{
}
}

namespace evproto
{
namespace gpb = ::google::protobuf;
}

#endif  // EVPROTO_COMMON_H
