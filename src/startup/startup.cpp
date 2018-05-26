// very simple startup code with definition of handlers for all cortex-m cores

// location of these variables is defined in linker script
extern unsigned __data_load;

extern unsigned __data_start;
extern unsigned __data_end;

extern unsigned __bss_start;
extern unsigned __bss_end;

extern unsigned __heap_start;

extern unsigned __init_array_start;
extern unsigned __init_array_end;

extern unsigned __fini_array_start;
extern unsigned __fini_array_end;

// main application
extern void main_app();

void copy_data() {
    unsigned *src = &__data_load;
    unsigned *dst = &__data_start;
    while (dst < &__data_end) {
        *dst++ = *src++;
    }
}

void zero_bss() {
    unsigned *dst = &__bss_start;
    while (dst < &__bss_end) {
        *dst++ = 0;
    }
}

void fill_heap(unsigned fill=0x55555555) {
    unsigned *dst = &__heap_start;
    register unsigned *msp_reg;
    __asm__("mrs %0, msp\n" : "=r" (msp_reg) );
    while (dst < msp_reg) {
        *dst++ = fill;
    }
}

void call_init_array() {
    unsigned *tbl = &__init_array_start;
    while (tbl < &__init_array_end) {
        ((void (*)())*tbl++)();
    }
}

void call_fini_array() {
    unsigned *tbl = &__fini_array_start;
    while (tbl < &__fini_array_end) {
        ((void (*)())*tbl++)();
    }
}

// reset handler
void RESET_handler() {
    copy_data();
    zero_bss();
    fill_heap();
    call_init_array();
    // run application
    main_app();
    // call destructors for static instances
    call_fini_array();
    // stop
    while (true);
}
