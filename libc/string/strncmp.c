#include "../include/string.h"


int strncmp(const char* s1, const char* s2, size_t n)
{
	while(n)
	if(*s1++ != *s2++)
		return *(const unsigned char*)s1 - *(const unsigned char*)s2;
	return 0;
}
//this utility is similar to the strcmp in that it compares as well 
// however it accepts a third parameter that tells the utility to compare the first n characters
