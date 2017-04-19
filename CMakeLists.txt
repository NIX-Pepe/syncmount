cmake_minimum_required(VERSION 2.6)
project(syncmount)

add_executable(syncmount main.cpp)

install(TARGETS syncmount RUNTIME DESTINATION bin)
