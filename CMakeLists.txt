project(fdf)

cmake_minimum_required(VERSION 3.13)

aux_source_directory(. src)
find_library(OGL OpenGL)
find_library(AKIT AppKit)
add_executable(fdf ${src})
target_link_libraries(fdf ${OGL} ${AKIT} /usr/local/lib/libmlx.a ${CMAKE_CURRENT_SOURCE_DIR}/libftprintf/libftprintf.a)
include_directories(/usr/local/include/)
