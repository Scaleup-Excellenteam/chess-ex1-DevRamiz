add_executable(tests PriorityQueueTests.cpp)

target_include_directories(tests PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/tests)

target_link_libraries(tests PRIVATE chess_lib)
add_test(NAME runTests COMMAND tests)