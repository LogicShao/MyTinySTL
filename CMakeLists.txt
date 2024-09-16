cmake_minimum_required(VERSION 3.20.0)
project(MyTinySTL)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(MySTL STATIC ${srcs})
target_include_directories(MySTL PUBLIC include)

add_executable(main src/main.cpp)
target_include_directories(main PUBLIC include)
target_link_libraries(main MySTL)