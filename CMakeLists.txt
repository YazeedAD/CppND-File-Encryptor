cmake_minimum_required(VERSION 3.16)
project(UdacityCapstone_AES256)

set(CMAKE_CXX_STANDARD 14)

add_executable(UdacityCapstone_AES256 src/main.cpp include/lookup_tables.h src/AES256.cpp include/AES256.h src/util.cpp include/util.h src/AES256Mode.cpp include/AES256Mode.h)

add_executable(utest test/utest_aes256.cpp include/lookup_tables.h src/AES256.cpp include/AES256.h src/util.cpp include/util.h src/AES256Mode.cpp include/AES256Mode.h)