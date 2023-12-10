file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

enable_testing()
find_package(GTest REQUIRED)
add_executable(queue_test ${srcs})

target_include_directories(queue_test PUBLIC ${GTest_INCLUDE_DIRS})

target_link_libraries(queue_test PUBLIC swam_concurrency GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(queue_test)
