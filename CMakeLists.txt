cmake_minimum_required(VERSION 3.26)
project(osp2023_A1_startup)

set(CMAKE_CXX_STANDARD 20)

include_directories(a1-startup/copier_files)
# include_directories(a1-startup/mtcopier_files)

add_executable(osp2023_A1_startup
        a1-startup/copier_files/main.cpp
        a1-startup/copier_files/reader.cpp
        a1-startup/copier_files/reader.h
        a1-startup/copier_files/writer.cpp
        a1-startup/copier_files/writer.h)
#        a1-startup/mtcopier_files/main.cpp
#        a1-startup/mtcopier_files/reader.cpp
#        a1-startup/mtcopier_files/reader.h
#        a1-startup/mtcopier_files/writer.cpp
#        a1-startup/mtcopier_files/writer.h)
