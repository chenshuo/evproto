set(evproto_SRCS
  eventloop.cc
  evproto.cc
  httpserver.cc
  rpcchannel.cc
  rpccontroller.cc
  rpcserver.cc
  )

add_library(evproto ${evproto_SRCS})

