#include "../include/string.h"

char* strstr(char* s1, const* char s2){
	size_t n = strlen(s2);
	while(*s1){
		if(!memcmp(s1++,s2,n)){
			return s1 - 1;
		}
			
		return 0;
	}
	
}

//similar to the prevous utility, this utility searches s1 for the presence of s2
// if found the utility will return a pointer to the location of s2
