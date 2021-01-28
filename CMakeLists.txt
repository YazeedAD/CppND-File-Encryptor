cmake_minimum_required(VERSION 3.16)
project(UdacityCapstone_AES256)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS random filesystem)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(FileEncryptor src/main.cpp include/lookup_tables.h src/AES256.cpp include/AES256.h src/util.cpp include/util.h src/AES256Mode.cpp include/AES256Mode.h src/cli.cpp include/cli.h)
    add_executable(utest test/utest_aes256.cpp include/lookup_tables.h src/AES256.cpp include/AES256.h src/util.cpp include/util.h src/AES256Mode.cpp include/AES256Mode.h src/cli.cpp include/cli.h)
    target_link_libraries(FileEncryptor  ${Boost_LIBRARIES})
    target_link_libraries(utest  ${Boost_LIBRARIES})

endif()



