# Bare metal for ARM cortex-M using C++

This example show how to write simple startup code in C++ and use Cmake for building.
Presented example is very simple "Hello blinky" program for STM32F0xx which blink LED connected to GPIO A15 and blink on maximum speed (no delay or timers are used).

## C++ benefits for embedded

- C++ provides many advantages over C, like OOP, namespaces, templates, overloading, references, ...
- Also allow to write very clean and readable source code and very efficient final code

### Limitations, or not recommended C++ features in embedded

- Do not use new and delete (unless you define your own on heap or in static array - memory pool)
- No exceptions are allowed and also no components which using exceptions (like most of `std::`, ...)
- No RTTI, ..

*Everything from this is also possible to use, but then is necessary to implement some stub functions for heap management and basic IO for `newlib`. Final compiled program can be much bigger in memory (often more than 80KB) and this also brings some overhead, which is often useless in embedded applications.*

## Code structure

- `CmakeLists.txt` is Cmake building script
- `src` folder contain application code
- `src/startup` folder contain all startup code
- `ld` folder contain linker scripts
- `cmake/arm-none-eabi.cmake` is platform file which define compilers and configuration for this project

## Dependencies

- gcc-arm for embedded [download here](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
- [cmake](https://cmake.org/download/)

*this don't need any other dependencies like CMSIS library for building. Example is real bare metal code.*

## Building

```
mkdir _build
cd _build
cmake -D CMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi.cmake ..
make
```

or use `make bin`, `srec`, `hex`, `flash`, ...

## Change architecture

in file CmakeLists.txt change CPU_OPTIONS:
- architecture options:
    - Cortex-M0: `set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m0")`
    - Cortex-M0+ `set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m0plus")`
    - Cortex-M3 `set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m3")`
    - Cortex-M4 `set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m4")`
    - Cortex-M7 `set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m7")`
    - Cortex-M23: `set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m23")`
    - Cortex-M33: `set(CPU_OPTIONS "${CPU_OPTIONS} -mthumb -mcpu=cortex-m33")`

- floating point, add options to CPU_OPTIONS:
    - soft float `-mfloat-abi=softfp`
    - hard float `-mfloat-abi=hard`
- for floating point also add fpv architecture
    - Cortex-M4 single precision `-mfpu=fpv4-sp-d16`
    - Cortex-M7 and M33 single-precision `-mfpu=fpv5-sp-d16`
    - Cortex-M7 and M33 signle and double-precision `-mfpu=fpv5-d16`

*Detailed info about options is in readme: gcc-arm directory: share/doc/gcc-arm-none-eabi/readme.txt
or in [ARM-Options](https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html) document*
