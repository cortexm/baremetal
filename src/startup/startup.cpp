// very simple startup code with definition of handlers for all cortex-m cores

// location of these variables is defined in linker script
extern unsigned _data_load;

extern unsigned _data_start;
extern unsigned _data_end;

extern unsigned _bss_start;
extern unsigned _bss_end;

extern unsigned _heap_start;

extern unsigned _init_array_start;
extern unsigned _init_array_end;

extern unsigned _fini_array_start;
extern unsigned _fini_array_end;

// main application
extern void main_app();

void copy_data() {
    unsigned *src = &_data_load;
    unsigned *dst = &_data_start;
    while (dst < &_data_end) {
        *dst++ = *src++;
    }
}

void zero_bss() {
    unsigned *dst = &_bss_start;
    while (dst < &_bss_end) {
        *dst++ = 0;
    }
}

void fill_heap(unsigned fill=0x55555555) {
    unsigned *dst = &_heap_start;
    register unsigned *msp_reg;
    __asm__("mrs %0, msp\n" : "=r" (msp_reg) );
    while (dst < msp_reg) {
        *dst++ = fill;
    }
}

void call_ctors() {
    unsigned *tbl = &_init_array_start;
    while (tbl < &_init_array_end) {
        ((void (*)())*tbl++)();
    }
}

void call_dtors() {
    unsigned *tbl = &_fini_array_start;
    while (tbl < &_fini_array_end) {
        ((void (*)())*tbl++)();
    }
}

// reset handler
void RESET_handler() {
    copy_data();
    zero_bss();
    fill_heap();
    call_ctors();
    // run application
    main_app();
    // call destructors for static instances
    call_dtors();
    // stop
    while (true);
}
