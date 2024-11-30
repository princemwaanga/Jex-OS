#include "../include/string.h"
char* strchr(const char* s, int c){
	while(*s!=(char)c)
	if(!*s++)
	return 0;
	return (char*)s;
}

//this utiltiy accepts a string array and character(represented as int) and 
// searches the array for the existence of the character
