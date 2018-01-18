# Bare metal example for ARM cortex-M using C++

This example show how to write simple startup code in C++ and use Cmake for building.
Presented example is very simple "Hello blinky" program for STM32F0xx which blink LED connected to GPIO A15 and blink on maximum speed (no delay or timers are used).

## C++ advantages for embedded

- Possible to use latest standards (C++17)
- Very small compiled code (comparable with C)

### Limitations, or not recommended C++ features in embedded

- Do not use new and delete (unless you define your own on heap or in static array - memory pool)
- No exceptions are allowed and also no components which using exceptions (like most of `std::`, ...)
- no RTTI, ..

*Everything from this is also possible to use, but then is necessary to implement some stub functions for heap management and basic IO for `newlib`, after program can be much bigger in memory (often more than 80KB).*

## Code structure

- `CmakeLists.txt` is Cmake building script
- `src` folder contain application code
- `src/startup` folder contain all startup code + linker script
- `cmake/arm-none-eabi.cmake` is platform file which define compilers and configuration of cmake for this project

## Dependencies

- arm-gcc for embedded [download here](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
- [cmake](https://cmake.org/download/)

- no need any dependencies like CMSIS library for building of this example.

## Building

```
mkdir _build
cd _build
cmake -D CMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi.cmake ..
make
```

or use `make bin`, `srec`, `hex`, `flash`, ...
