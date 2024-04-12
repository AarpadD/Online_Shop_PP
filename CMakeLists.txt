cmake_minimum_required(VERSION 3.27)
project(OnlineShop C)

set(CMAKE_C_STANDARD 11)

add_executable(OnlineShop main.c
        commands.c
        data_structures.h
        files_io.c
)
