cmake_minimum_required(VERSION 3.16)
project(UdacityCapstone_AES256)

set(CMAKE_CXX_STANDARD 14)

add_executable(UdacityCapstone_AES256 src/main.cpp src/sbox.h src/AES256.cpp src/AES256.h test/utest_aes256.cpp)

add_executable(test test/utest_aes256.cpp src/main.cpp src/sbox.h src/AES256.cpp src/AES256.h test/utest_aes256.cpp)