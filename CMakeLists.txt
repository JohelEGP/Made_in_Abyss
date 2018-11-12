cmake_minimum_required(VERSION 3.11.0)
project(Made_in_Abyss LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

include(mia_find_dependencies)

add_library(mia INTERFACE)
add_library(mia::mia ALIAS mia)
target_include_directories(mia INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(mia INTERFACE cxx_std_17)
target_link_libraries(mia INTERFACE
    GSL
    Boost::boost
    range-v3
    jegp::jegp
    units)

add_executable(Made_in_Abyss src/mia.cpp)
target_link_libraries(Made_in_Abyss PRIVATE mia::mia)

option(MIA_TEST_EXTENSIVELY "Performs a combinatorial explosion of test cases.")
include(CTest)
if(BUILD_TESTING)
    include(mia_add_tests)
endif()
