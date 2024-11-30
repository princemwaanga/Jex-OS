#include "../include/string.h"


int strcmp(const char* s1, const char* s2)
{
	while(*s1&&(*s1 == *s2))
	s1++,s2++;

	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
//this utility accepts two string arrays and compares them.
//if the return value is less than zero, it indicates s1 is less than s2
