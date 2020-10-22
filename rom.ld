OUTPUT_FORMAT(binary)

rom_start     = 0x00fc0000 ;
kernel_ram_start = 0x00000400 ;

SECTIONS
{
	. = rom_start ;

    .text :
    {
        *(.text) ;
        *(.rodata) ;
		. = ALIGN(0x10) ;
		_etext = . ;
    }

    .data kernel_ram_start : AT(ADDR(.text) + SIZEOF(.text))
    {
		_data = . ;
        *(.data) ;
		_edata = . ;
    }

    .bss ALIGN(0x2) :
    {
		_bss = . ;
        *(COMMON) ;
        *(.bss) ;
		_bssend = . ;
    }
}
