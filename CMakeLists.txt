

cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)

project(ImPondering)

set(IMP_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(USER_LOCAL "/set_me" CACHE STRING "/usr/local equivalent")

# output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${IMP_SOURCE_DIR}/bin) # exe
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${IMP_SOURCE_DIR}/bin) # .dylib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${IMP_SOURCE_DIR}/lib) # .a
make_directory(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
make_directory(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(IMP_IMGUI_DIR ${IMP_SOURCE_DIR}/deps/imgui)
set(IMP_PONDER_DIR ${IMP_SOURCE_DIR}/deps/ponder)

add_subdirectory(deps/ponder)
add_subdirectory(src)
