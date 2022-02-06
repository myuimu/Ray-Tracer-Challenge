cmake_minimum_required(VERSION 3.14)
project(RAY_TRACER 
        VERSION 0.1.0 
        LANGUAGES CXX)

set(BOOST_INCLUDE_DIRS /opt/homebrew/Cellar/boost/1.76.0/include/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --std=c++17")

add_library(ray SHARED
    src/tuple/tuple.cpp
    src/ray.cpp
)

add_executable(main
    src/main.cpp
    src/tuple/tuple.cpp
    src/ray.cpp
)

add_executable(test
    src/tuple/tuple.test.cpp
    src/tuple/tuple.cpp
    src/ray.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(test PRIVATE 
    ${BOOST_INCLUDE_DIRS}
)

set_target_properties(ray PROPERTIES PUBLIC_HEADER include/ray.h)

set_property(GLOBAL PROPERTY CXX_STANDARD 17)

add_test(NAME test COMMAND test)