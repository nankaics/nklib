cmake_minimum_required(VERSION 2.8)
project(nk CXX)

###############################################################################################################################
add_definitions (-D_DBG_)
#add_definitions (-D_PRT_)
#add_definitions (-D__PRT_GSLSOLVE)
#add_definitions (-D__PRT_Z3SOLVE)
#add_definitions (-D__PRT_POLYNOMIAL)
#add_definitions (-D__PRT_SVM_I)
#add_definitions (-D__PRT_POLYSVM)
#add_definitions (-D__PRT_INFER)
#add_definitions (-D__PRT_QUERY)
add_definitions (-D__PRT_STATISTICS)
add_definitions (-DSCRIPT)
###############################################################################################################################


###############################################################################################################################
#set(CMAKE_C_COMPILER             "clang")
#set(CMAKE_C_FLAGS                "-Wall -std=c99")
#set(CMAKE_C_FLAGS_DEBUG          "-g")
#set(CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
#set(CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
#set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_CXX_COMPILER             "clang++")
set(CMAKE_CXX_FLAGS                "-Wall -g -std=c++11")
#set(CMAKE_CXX_FLAGS                "-Wall -g -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
###############################################################################################################################
#

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
find_package(Z3 REQUIRED)
#find_package(GSL REQUIRED)

# add include dir and source dir into project
file(GLOB HEADER "src/*.h")
include_directories (src)
aux_source_directory(src SRCS)
#aux_source_directory(. src DIR_SRCS)

add_library(nk SHARED ${SRCS})
set_target_properties(nk PROPERTIES VERSION 1.0)
install(TARGETS nk LIBRARY DESTINATION lib)
#install(TARGETS nk ARCHIVE DESTINATION lib)
#install(FILES src/polynomial.h src/common.h src/color.h src/dbg.h DESTINATION include/nk)
install(FILES ${HEADER} DESTINATION include/nk)
