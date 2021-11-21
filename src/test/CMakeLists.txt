message("-- Building MAFU Core Test Suite")

file(GLOB_RECURSE MAFU_TEST_SHARED_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h
                                          ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
list(SORT MAFU_TEST_SHARED_SOURCE)

add_executable(run_mafu_tests ${MAFU_TEST_SHARED_SOURCE} AllTests.cpp)
target_include_directories(run_mafu_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests)

target_link_libraries(run_mafu_tests
        ${GTEST_LIBRARIES}
        metaphase_core)

set_target_properties(run_mafu_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test/mafu_tests)
