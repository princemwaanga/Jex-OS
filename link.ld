ENTRY(_start)		/*the name of the entry lable*/

SECTIONS{
	. = 0x00100000;	/*the code should be loaded at 1 MB */

	.text ALIGN (0x1000) : /*align at 4kb*/
	{
		*(.text)			/*all text sections from all files*/
	}

	.rodata ALIGN (0x1000) : /* align at 4 KB*/
	{
		*(.rodata*) 		/*all read-only data sections from all files*/
	}

	.data ALIGN (0x1000) : /* align at 4KB*/
	{
		*(.data)			/*all data sections from all files*/
	}

	.bss ALIGN (0x1000) : /* align at 4KB*/
	{
		*(COMMON)			/* all COMMON sections from all files*/
		*(.bss)				/*all bss sections from all files*/
	}
}
