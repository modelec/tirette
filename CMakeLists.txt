cmake_minimum_required(VERSION 3.25)
project(tirette)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TCPSocket REQUIRED TCPSocket)

find_package(wiringpi REQUIRED)

add_executable(tirette main.cpp
        MyClient.cpp
        MyClient.h)

target_link_libraries(tirette TCPSocket)

target_link_libraries(tirette wiringpi)