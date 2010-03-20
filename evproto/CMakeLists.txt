set(evproto_SRCS
  eventloop.cc
  evproto.cc
  httpserver.cc
  )

add_library(evproto ${evproto_SRCS})

