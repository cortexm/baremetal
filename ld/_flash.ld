SECTIONS {
    . = ORIGIN(FLASH);
    .text : {
        KEEP(*(.stack))
        KEEP(*(.vectors))
        KEEP(*(.vectors*))
        KEEP(*(.text))
        *(.text*)
        KEEP(*(.rodata))
        *(.rodata*)
    } >FLASH

    .init_array ALIGN(4): {
        _init_array_start = .;
        KEEP(*(.init_array))
        _init_array_end = .;
    } >FLASH

    .fini_array ALIGN(4): {
        _fini_array_start = .;
        KEEP(*(.fini_array))
        _fini_array_end = .;
    } >FLASH
}
