cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(processreader VERSION 0.0.1 DESCRIPTION "processreader" LANGUAGES CXX)

add_executable(processreader src/main.cc src/processreader.cc src/queue.cc)

target_link_libraries(processreader)

set_property(TARGET processreader PROPERTY CXX_STANDARD 98)