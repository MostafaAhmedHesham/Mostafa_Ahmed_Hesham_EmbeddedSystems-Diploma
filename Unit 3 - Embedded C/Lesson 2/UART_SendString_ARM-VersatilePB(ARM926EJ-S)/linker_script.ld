ENTRY(reset)

MEMORY
{
	mem (rwx) : ORIGIN = 0x00000000, LENGTH = 64M
}

SECTIONS
{
	. = 0x10000;
	.reset . :
	{
		startup.o(.text)
	}> mem
	.text :
	{
		*(.text) *(.rodata)
	}> mem
	.data :
	{
		*(.data)
	}> mem
	.bss :
	{
		*(.bss) *(.COMMON)
	}> mem
	. = . + 0x1000;
	stack_top = .;
}