// handlers definition code

// undefined handler point to this function, this stop MCU
// this function name must by not mangled, so must be C
extern "C" void __stop() { while (true); }

// handlers for cortex-M core
// these handler are 'weak' and can be overwritten by non-week function
// default is __stop() function
__attribute__((weak, alias("__stop"))) void RESET_handler();
__attribute__((weak, alias("__stop"))) void NMI_handler();
__attribute__((weak, alias("__stop"))) void HARDFAULT_handler();
__attribute__((weak, alias("__stop"))) void MEMMANAGE_handler();
__attribute__((weak, alias("__stop"))) void BUSFAULT_handler();
__attribute__((weak, alias("__stop"))) void USAGEFAULT_handler();
__attribute__((weak, alias("__stop"))) void SVCALL_handler();
__attribute__((weak, alias("__stop"))) void DEBUGMONITOR_handler();
__attribute__((weak, alias("__stop"))) void PENDSV_handler();
__attribute__((weak, alias("__stop"))) void SYSTICK_handler();

// dummy handler
__attribute__((weak, alias("__stop"))) void DUMMY_handler();

// vector table for handlers
__attribute__((section(".vectors"), used)) void (*isr_vectors[])() = {
    RESET_handler,
    NMI_handler,
    HARDFAULT_handler,
    MEMMANAGE_handler,
    BUSFAULT_handler,
    USAGEFAULT_handler,
    DUMMY_handler,
    DUMMY_handler,
    DUMMY_handler,
    DUMMY_handler,
    SVCALL_handler,
    DEBUGMONITOR_handler,
    DUMMY_handler,
    PENDSV_handler,
    SYSTICK_handler,
};
