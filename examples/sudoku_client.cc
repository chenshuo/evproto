#include "examples/sudoku.pb.h"
#include "evproto/eventloop.h"
#include "evproto/evproto.h"
#include "evproto/rpcchannel.h"
#include "evproto/rpccontroller.h"

#include <glog/logging.h>
#include <google/protobuf/descriptor.h>

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  evproto::initialize(argc, argv);

  evproto::EventLoop loop;
  evproto::RpcChannel channel(&loop);
  CHECK(channel.addServer("127.0.0.1", 2000));
  sudoku::SudokuService::Stub stub(&channel);
  cout << stub.GetDescriptor()->name() << endl;
  cout << stub.GetDescriptor()->full_name() << endl;

  evproto::RpcController controller;
  sudoku::SudokuRequest req;
  req.set_checkerboard("1312313.312");
  sudoku::SudokuResponse resp;
  stub.Solve(&controller, &req, &resp, NULL);
  loop.loop();
}

