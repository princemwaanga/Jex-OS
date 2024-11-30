#include "../include/string.h"

size_t strlen(const char* str)
{
	size_t ret = 0;
	while(str[ret]!=0){
		ret++;
	}
	return ret;
}
//this utility accepts a character array and returns its length
