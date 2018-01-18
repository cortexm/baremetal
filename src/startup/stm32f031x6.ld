MEMORY {
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 32K
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 4K
}

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

SECTIONS {
    _stacktop = ORIGIN(SRAM) + LENGTH(SRAM);
    _data_load = LOADADDR(.data);
    . = ORIGIN(SRAM);

    .data ALIGN(4) : {
        _data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } >SRAM AT >FLASH

    .bss ALIGN(4) (NOLOAD) : {
        _bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _bss_end = .;
        *(.noinit)
        *(.noinit*)
    } >SRAM

    . = ALIGN(4);
    _heap_start = .;
}
