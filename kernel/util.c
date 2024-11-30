#include "../cpu/types.h"
#include "../drivers/io.h"
#include "kbd.h"
#include "../libc/include/string.h"

void memory_copy(char *source, char *dest, int nbytes){
	int i;
	for(i = 0; i < nbytes; i++){
		*(dest + i) = *(source + i);
	}	
}

/* K&R */
void int_to_ascii(int n, char str[]){
	int i, sign;
	if((sign = n) < 0) n = -n;
	i = 0;
	do{
		str[i++] = n % 10 + '0';
	}while((n /= 10) > 0);

	if (sign < 0) str[i++] = '-';
	str[i] = '\0';
    reverse(str);
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    s32 tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}

char *getS(){
    char *buffer;
    kprint("\nplease enter the word (press enter to continue): ");
    strcpy(&buffer[strlen(buffer)], '1');
    while (1)
    {
    
        u8 bytes;
		    while(bytes = scan()){
		 	    if(bytes == 0x1c){ //0x1c is the enter button hex code
                    //memset(&buffer[0],0,sizeof(buffer));
                
                    return buffer;
                    memset(&buffer[0],0,sizeof(buffer));
		 		    break; //come out of loop
                }
            else{
				// This is linked up to the kbd for mapping the keys
		 		char c = normalmap[bytes];
		 		char* s;
				if (c == '\b'){
					// moves the cursor back 2 steps to remove the last character
					backspace();
					// Sets the last character to '\0'
					Kbackspace(buffer);
					
					break;
				}
				if (c == '\t'){
					kprint(" ");
					int len = strlen(s);
					buffer[len] = " ";
				}
				else{
					s = ctos(s, c);
		 			kprint(s);
		 			strcpy(&buffer[strlen(buffer)], s);
				}	
		 	}
         }
    }
}