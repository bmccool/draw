cmake_minimum_required(VERSION 3.15)
project(draw C)


add_library(draw src/draw.c)
target_include_directories(draw PUBLIC include)

set_target_properties(draw PROPERTIES PUBLIC_HEADER "include/draw.h")

install(TARGETS draw)
