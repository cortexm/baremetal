// define used registers
static volatile unsigned &RCC_AHB1 = *reinterpret_cast<unsigned *>(0x40021014);
static volatile unsigned &GPIOA_MODER = *reinterpret_cast<unsigned *>(0x48000000);
static volatile unsigned &GPIOA_BSRR = *reinterpret_cast<unsigned *>(0x48000018);

// application
void main_app() {
    RCC_AHB1 |= 1 << 17;  // enable clock for GPIOA
    GPIOA_MODER |= 1 << (15 * 2);  // set output on GPIOA.P15
    while (true) {
        GPIOA_BSRR = 1 << 15;  // set output on GPIOA.P15
        GPIOA_BSRR = 1 << (15 + 16);  // clear output on GPIOA.P15
    }
}
