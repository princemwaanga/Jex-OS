#ifndef _STRING_H
#define _STRING_H 1

#include "../../drivers/types.h"
#include "../../drivers/io.h"

#include "stdarg.h"


int memcmp(const void* aptr, const void* bptr, size_t size); size_t strlen(const char*);
char* strcat(char* d, const char* s);
char* strcpy(char* d, const char* s);
int strcmp(const char* s1, const char* s2);
char *strncat(char *dest, const char* src, size_t n);
char* strncpy(char* dest, const char* src, size_t n);
char* strstr(char* s1, const char* s2);
char *strchr(const char*s, int c);
int strncmp(const char* s1, const char* s2, size_t n);
char *ctos(char s[2], const char c);
void *memset(void* bufptr, int value, size_t size);
void Kbackspace(char s[]); 


//Just some more common stuff common stuff

u16 inw(u16 port);
void shutdown_power_off (void);
void PANIC (const char *msg);

// Printf setup
int vsprintf(char *buf, const char *fmt, va_list args);
void printF (const char *fmt, ...);

// memory assignment
u32 kmalloc(u32 sz);  // vanilla memory allocation
u32 kmalloc_p(u32 size, /*u32 *phys*/ int align); // returns a physical address.
u32 kmalloc_ap(u32 size,int align, u32 *phys); // page aligned and returns a physical address.
u32 kmalloc(u32 sz); // vanilla (normal)

#endif
