# That file is here only to make IDE's happy so they could index all source files.
# Real building happens through Makefile.

cmake_minimum_required(VERSION 3.9)
project(osuds)

set(CMAKE_CXX_STANDARD 20)

# Set to your devkitPro's installation dir if environment variable does not exist.
set(DEVKITPRO C:/devkitpro)

include_directories(${DEVKITPRO}/libnds/lib)
include_directories(${DEVKITPRO}/libnds/include)
include_directories(${DEVKITPRO}/libnds/include/nds)
include_directories(${DEVKITPRO}/libnds/include/nds/arm9)
include_directories(${DEVKITPRO}/devkitARM)
include_directories(${DEVKITPRO}/devkitARM/arm-none-eabi/include)
include_directories(source)
include_directories(fonts)
include_directories(data)
include_directories(build)

link_directories(${DEVKITPRO}/libnds/lib)
link_directories(${DEVKITPRO}/libnds/include)
link_directories(${DEVKITPRO}/libnds/include/nds)
link_directories(${DEVKITPRO}/libnds/include/nds/arm9)

add_compile_definitions(ARM9)
add_compile_definitions(ARM7)
add_compile_definitions(iprintf=printf)

FILE(GLOB_RECURSE src *.cpp *.hpp *.c *.h)

add_executable(osuds ${src})