// define used registers
#define RCC_AHB1 *(volatile unsigned *)(0x40021014)
#define GPIOA_MODER *(volatile unsigned *)(0x48000000)
#define GPIOA_BSRR *(volatile unsigned *)(0x48000018)

// application
void main_app() {
    RCC_AHB1 |= 1 << 17;  // enable clock for GPIOA
    GPIOA_MODER |= 1 << (15 * 2);  // set output on GPIOA.P15
    while (true) {
        GPIOA_BSRR = 1 << 15;  // set output on GPIOA.P15
        GPIOA_BSRR = 1 << (15 + 16);  // clear output on GPIOA.P15
    }
}
