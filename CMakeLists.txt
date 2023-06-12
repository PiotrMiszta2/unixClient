cmake_minimum_required(VERSION 3.24)
project(client C)

set(CMAKE_C_STANDARD 17)

file(GLOB message "${CMAKE_SOURCE_DIR}/src/messages/*.c")
file(GLOB util "${CMAKE_SOURCE_DIR}/src/util/*.c")


include_directories(${CMAKE_SOURCE_DIR}/include/messages/
                    ${CMAKE_SOURCE_DIR}/include/util
                    ${CMAKE_SOURCE_DIR}/include )

add_executable(client src/main.c src/connection.c ${message} ${util})
