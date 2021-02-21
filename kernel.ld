OUTPUT_FORMAT(binary)

kernel_start     = 0x00fc0000 ;
kernel_ram_start = 0x00000400 ;

SECTIONS
{
	. = kernel_start ;

    .text :
    {
        *(.text) ;
        *(.rodata) ;
	*(.rodata.str1.1) ;
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
