cmake_minimum_required(VERSION 3.0)

# project name
project(bare_metal)

# select linker script
set(LINKER_SCRIPT "src/startup/stm32f031x6.ld")

add_compile_options(
    -Wall
    -pedantic
    -Wextra
    -fstrict-volatile-bitfields
    -ffunction-sections
)

# define compiler options more info in: gcc-arm directory: share/doc/gcc-arm-none-eabi/readme.txt
set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m0")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPU_OPTIONS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPU_OPTIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-use-cxa-atexit")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")

# optimizations (-O0 -O1 -O2 -O3 -Os -Ofast -Og -flto)
set(OPTIMIZATION_DEBUG "-Og")
set(OPTIMIZATION_RELEASE "-O2 -flto")

set(CMAKE_C_FLAGS_DEBUG "${OPTIMIZATION_DEBUG} -g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${OPTIMIZATION_DEBUG} -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${OPTIMIZATION_RELEASE}")
set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZATION_RELEASE}")

# select build type, can be Debug, Release
set(CMAKE_BUILD_TYPE Debug)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

link_directories(
    ${CMAKE_SOURCE_DIR}
)

# list of modules to build final firmware (without extension .c or .cpp)
add_executable(${PROJECT_NAME}.elf
    src/main
    src/startup/startup
    src/startup/stack
    src/startup/handlers_cm
)

include("cmake/flash.cmake")
