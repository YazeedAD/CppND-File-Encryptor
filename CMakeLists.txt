cmake_minimum_required(VERSION 3.16)
project(UdacityCapstone_AES256)

set(CMAKE_CXX_STANDARD 14)

add_executable(UdacityCapstone_AES256 main.cpp sbox.h AES256.cpp AES256.h)