#include "sudoku.pb.h"
#include "evproto/rpcchannel.h"

#include <google/protobuf/descriptor.h>

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  evproto::RpcChannel channel;
  sudoku::SudokuService::Stub stub(&channel);
  cout << stub.GetDescriptor()->name() << endl;
  cout << stub.GetDescriptor()->full_name() << endl;
  stub.Solve(NULL, NULL, NULL, NULL);
}

