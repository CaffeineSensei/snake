cmake_minimum_required(VERSION 3.22)
project(snake)

set(CXX_STANDARD 20)

aux_source_directory(. src)
add_executable(snake ${src})