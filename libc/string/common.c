#include "../include/string.h"

u16 inw(u16 port)
{
	u16 ret;
	__asm__ __volatile__("inw %1, %0" : "=a"(ret): "dN"(port));
	return ret;
}