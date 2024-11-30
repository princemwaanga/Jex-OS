#include "../include/string.h"

char* strcpy(char* dest, const char* src){
	char* tmp = dest;

	while((*dest++ = *src++) != 0);

	return tmp;
}
//this utiltiy accepts two string arrays and copies the second string 
