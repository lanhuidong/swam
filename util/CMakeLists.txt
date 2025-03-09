file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

set(libname swam_util)

add_library(${libname} SHARED ${srcs})

target_include_directories(${libname} PUBLIC include)