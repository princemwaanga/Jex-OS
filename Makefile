C_FILES = kernel/kernel.c \
			drivers/ports.c \
			drivers/screen.c\
			drivers/io.c\
			kernel/util.c\
			libc/string/ctos.c\
			libc/string/memcmp.c\
			libc/string/common.c\
			libc/string/strcat.c\
			libc/string/strlen.c\
			libc/string/memset.c\
			libc/string/strcpy.c\
			libc/string/strcmp.c\
			libc/string/strncmp.c\
			libc/string/backspace.c\
			libc/string/kheap.c\
			libc/string/shutdown.c\
			libc/string/vsprintf.c\
			libc/string/printk.c\
			kprograms/art.c\
			kprograms/date.c\
			cpu/idt.c\
			cpu/isr.c\
			cpu/timer.c\
			
			
			
			
			
		  	
OBJECTS = $(C_FILES:.c=.o)
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-stack-protector \
			-nostartfiles -nodefaultlibs 
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf32
 
run: os.iso
		 gnome-terminal; qemu-system-x86_64 -display curses -cdrom JEX.iso
	
os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot\
	 -boot-load-size 4 -A os -input-charset utf8 \
	 -quiet -boot-info-table -o JEX.iso iso 

 
kernel.elf: $(OBJECTS) boot.o cpu/interrupt.o
	ld $(LDFLAGS) boot.o cpu/interrupt.o $(OBJECTS) -o kernel.elf

cpu/interrupt.o: cpu/interrupt.asm
	nasm -f elf32 $< -o $@	

%.o:
	$(CC) -c $(@:.o=.c) $(CFLAGS) $< -o $@
	
boot.o: boot.asm
	nasm -f elf32 $< -o $@



clean:
	rm -rf *.o kernel.elf JEX.iso
	rm -rf kernel/*.o drivers/*.o cpu/*.o libc/string/*.o kprograms/*.o process/*.o filesystem/*.o
	
