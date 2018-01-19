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
