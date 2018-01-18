// very simple startup code with definition of handlers for all cortex-m cores

// location of these variables is defined in linker script
extern unsigned _data_load;

extern unsigned _data_start;
extern unsigned _data_end;

extern unsigned _bss_start;
extern unsigned _bss_end;

extern unsigned _init_array_start;
extern unsigned _init_array_end;

extern unsigned _fini_array_start;
extern unsigned _fini_array_end;

// main application
extern void main_app();

// reset handler
void RESET_handler() {
    unsigned *src, *dst;

    // copy data
    src = &_data_load;
    dst = &_data_start;
    while (dst < &_data_end) {
        *dst++ = *src++;
    }

    // zero bss
    dst = &_bss_start;
    while (dst < &_bss_end) {
        *dst++ = 0;
    }

    // get current stack pointer
    register unsigned *msp_reg;
    __asm__("mrs %0, msp\n" : "=r" (msp_reg) );

    // fill unused SRAM
    dst = &_bss_end;
    while (dst < msp_reg) {
        *dst++ = 0x55555555;
    }

    // call constructors for static instances
    dst = &_init_array_start;
    while (dst < &_init_array_end) {
        ((void (*)())*dst++)();
    }

    // run application
    main_app();

    // call destructors for static instances
    dst = &_fini_array_start;
    while (dst < &_fini_array_end) {
        ((void (*)())*dst++)();
    }

    // stop
    while (true);
}
