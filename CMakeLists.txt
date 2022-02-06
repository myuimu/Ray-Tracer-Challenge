cmake_minimum_required(VERSION 3.14)
project(RAY_TRACER 
        VERSION 0.1.0 
        LANGUAGES CXX)

file(GLOB_RECURSE RAY_LIB_FILES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER RAY_LIB_FILES EXCLUDE REGEX "main|test")
file(GLOB_RECURSE RAY_MAIN_FILES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER RAY_MAIN_FILES EXCLUDE REGEX "test")
file(GLOB_RECURSE RAY_TEST_FILES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER RAY_TEST_FILES EXCLUDE REGEX "main")
set(BOOST_INCLUDE_DIRS /opt/homebrew/Cellar/boost/1.76.0/include/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --std=c++17")

add_library(ray SHARED
    ${RAY_LIB_FILES}
)

add_executable(main
    ${RAY_MAIN_FILES}
)

add_executable(test
    ${RAY_TEST_FILES}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(test PRIVATE 
    ${BOOST_INCLUDE_DIRS}
)

set_target_properties(ray PROPERTIES PUBLIC_HEADER include/ray.h)

set_property(GLOBAL PROPERTY CXX_STANDARD 17)

add_test(NAME test COMMAND test)