cmake_minimum_required(VERSION 3.9)
project(asyc)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g2 -ggdb -fpermissive -Wl,--as-needed")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall -fpermissive -Wl,--as-needed ")

#include_directories(/usr/include/hdf5/serial)
#include_directories(/usr/include/hdf)
#include_directories(/opt/hdf5/include)
#include_directories(/opt/hdf/include)
#include_directories(/opt/eccodes/include)
#link_directories(/opt/eccodes/lib)
#link_directories(/usr/lib/x86_64-linux-gnu/hdf5/serial/lib)
#link_directories(/opt/hdf/lib)
#link_directories(/opt/hdf5/lib)
#link_directories(/usr/lib64/hdf)
#include_directories(/opt/armadillo/include)
#link_directories(/opt/armadillo/lib64)
#link_libraries(log4cxx netcdf mfhdf df  hdf5_hl hdf5 eccodes pthread  /
#        boost_system.a boost_thread boost_filesystem.a boost_date_time.a boost_regex.a)

#include_directories(/opt/armadillo/include
#        /home/gaopeng/projects/qmod4)
#link_directories(/opt/armadillo/lib64
#        /home/gaopeng/projects/qmod4/bin/x64/Debug)

include_directories(Common)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(pthread boost_system boost_filesystem) #boost_thread boost_date_time

aux_source_directory(. DIR_PRESENT)
aux_source_directory(Common DIR_SRC)
add_executable(asyc ${DIR_PRESENT} ${DIR_SRC})