cmake_minimum_required(VERSION 3.8.0)
project(Made_in_Abyss LANGUAGES CXX)

add_executable(mia src/mia.cpp)

target_include_directories(mia PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(mia INTERFACE cxx_std_17)
