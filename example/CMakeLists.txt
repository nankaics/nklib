cmake_minimum_required(VERSION 2.8)
project(nktest CXX)

set(CMAKE_CXX_COMPILER             "clang++")
set(CMAKE_CXX_FLAGS                "-Wall -g -std=c++11")
#set(CMAKE_CXX_FLAGS                "-Wall -g -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
###############################################################################################################################
#

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake/")
find_package(Z3 REQUIRED)
find_package(GSL REQUIRED)

aux_source_directory(. SRCS)

add_executable(testnk ${SRCS})
target_link_libraries(testnk ${GSL_LIBRARIES})
target_link_libraries(testnk ${Z3_LIBRARY})
target_link_libraries(testnk nk)
