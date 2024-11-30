#include "../include/string.h"

char* strcat(char* dest, const char* src){
	char* tmp = dest;

	while(*dest)dest++;
	while((*dest++ = *src++)!=0);

	return tmp;
}

//this utility takes the string array src and appends it ti the end of the dest string array and 
// returns that concatenated value
