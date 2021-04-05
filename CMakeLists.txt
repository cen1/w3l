project(w3l)
cmake_minimum_required(VERSION 3.13)

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "6")
SET(VERSION_PATCH "0")

add_subdirectory(dll)
add_subdirectory(dll_27a)
#add_subdirectory(dll_29)
add_subdirectory(exe)
#add_subdirectory(exe_29)