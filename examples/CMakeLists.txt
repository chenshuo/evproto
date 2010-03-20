add_executable(eventloop_test eventloop_test.cc)
target_link_libraries(eventloop_test evproto)

add_custom_command(OUTPUT sudoku.pb.cc sudoku.pb.h
  COMMAND protoc
  ARGS --cpp_out . ${CMAKE_CURRENT_SOURCE_DIR}/sudoku.proto -I${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS sudoku.proto
  VERBATIM )

add_library(sudoku_proto sudoku.pb.cc)
target_link_libraries(sudoku_proto evproto)

add_executable(sudoku_server sudoku_server.cc)
target_link_libraries(sudoku_server sudoku_proto)

add_executable(sudoku_client sudoku_client.cc)
target_link_libraries(sudoku_client sudoku_proto)

