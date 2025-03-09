file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

enable_testing()
find_package(GTest REQUIRED)
add_executable(random_test ${srcs})

target_include_directories(random_test PUBLIC ${GTest_INCLUDE_DIRS})

target_link_libraries(random_test PUBLIC swam_util GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(random_test)
