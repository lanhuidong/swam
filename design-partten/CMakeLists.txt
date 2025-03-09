file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

set(libname swam_design_partten)

add_executable(${libname} ${srcs})

target_include_directories(${libname} PUBLIC include)