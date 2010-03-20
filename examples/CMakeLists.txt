add_executable(eventloop_test eventloop_test.cc)
target_link_libraries(eventloop_test evproto)

add_library(sudoku_proto sudoku.pb.cc)
target_link_libraries(sudoku_proto evproto)

add_executable(sudoku_server sudoku_server.cc)
target_link_libraries(sudoku_server sudoku_proto)

add_executable(sudoku_client sudoku_client.cc)
target_link_libraries(sudoku_client sudoku_proto)

