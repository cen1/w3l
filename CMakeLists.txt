set (CMAKE_SYSTEM_VERSION 6.1 CACHE TYPE INTERNAL FORCE)

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

target_compile_definitions(w3l PRIVATE WINVER=0x0601)
target_compile_definitions(w3l PRIVATE _WIN32_WINNT=0x0601)
