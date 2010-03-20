#include "sudoku.pb.h"

#include "evproto/evproto.h"
#include "evproto/eventloop.h"
#include "evproto/httpserver.h"
#include "evproto/rpcserver.h"

#include <glog/logging.h>

namespace sudoku
{

class SudokuServiceImpl : public SudokuService
{
};

}

int main(int argc, char* argv[])
{
  evproto::initialize(argc, argv);

  evproto::EventLoop loop;
  evproto::HttpServer httpServer(&loop, 2000);
  evproto::RpcServer rpcServer(&httpServer);
  sudoku::SudokuServiceImpl sudokuService;
  rpcServer.registerService(&sudokuService);

  int ret = loop.loop();
  LOG(INFO) << "EventLoop::loop() returns " << ret;
}

