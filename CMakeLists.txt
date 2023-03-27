cmake_minimum_required(VERSION 3.24)
project(Kafka_C_Backend C)

set(CMAKE_C_STANDARD 90)

add_executable(Kafka_C_Backend main.c backend_c++.cpp)
