cmake_minimum_required(VERSION 3.10)
project(BouncingBall)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(box2d URL https://github.com/erincatto/box2d/archive/refs/tags/v3.0.0.tar.gz)
FetchContent_MakeAvailable(box2d)

add_executable(BouncingBall main.cpp)

target_include_directories(BouncingBall PUBLIC ${box2d_SOURCE_DIR}/include  )

target_link_libraries(BouncingBall box2d)
