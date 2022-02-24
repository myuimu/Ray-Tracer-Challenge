cmake_minimum_required(VERSION 3.14)
project(RAY_TRACER 
        VERSION 0.1.0 
        LANGUAGES CXX)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

file(GLOB_RECURSE RAY_LIB_FILES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER RAY_LIB_FILES EXCLUDE REGEX "main")
file(GLOB_RECURSE RAY_MAIN_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE RAY_TEST_FILES CONFIGURE_DEPENDS "src/*.cpp" "tests/*.cpp")
list(FILTER RAY_TEST_FILES EXCLUDE REGEX "main")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -ffast-math -O3")

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

target_include_directories(test PUBLIC
    ${Boost_INCLUDE_DIR}
)
target_link_libraries(test PUBLIC Boost::unit_test_framework)

set_target_properties(ray PROPERTIES PUBLIC_HEADER include/ray_tracer.h)

set_property(GLOBAL PROPERTY CXX_STANDARD 17)

add_test(NAME test COMMAND test)