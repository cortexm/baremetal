// define used registers
static volatile unsigned &RCC_AHB1 = *reinterpret_cast<unsigned *>(0x40021014);
static volatile unsigned &GPIOA_MODER = *reinterpret_cast<unsigned *>(0x48000000);
static volatile unsigned &GPIOA_BSRR = *reinterpret_cast<unsigned *>(0x48000018);

// #include <cmath>

// application
void main_app() {
    RCC_AHB1 |= 0x00020000;  // enable clock for GPIOA
    GPIOA_MODER |= 0x40000000;  // set output on GPIOA.P15
    // double x = 0.0;
    // double y = 0.0;
    while (true) {
        // y = sin(x);
        // x += y;
        GPIOA_BSRR = 0x00008000;  // set output on GPIOA.P15
        GPIOA_BSRR = 0x80000000;  // clear output on GPIOA.P15
    }
}
