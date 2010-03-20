cmake_minimum_required(VERSION 2.6)

project(evproto CXX)

set(CXX_FLAGS
 -g
 -Wall
 -Wextra
 # -Werror
 -Wconversion
 -Wunused-parameter
 -Wold-style-cast
 -MMD
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -rdynamic
 -L/usr/local/lib
 -levent_core
 -levent_extra
 -levent_pthreads
 -lgflags
 -lglog
 -lprotobuf
 -lpthread
 -Wl,--rpath
 -Wl,/usr/local/lib
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})
add_subdirectory(evproto)
add_subdirectory(examples)

