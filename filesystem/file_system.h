//#ifndef _FILESYSTEM_H
//#define _FILESYSTEM_H 1

#include "../cpu/types.h"



void init_file_system();
int create_file(const char *name);
int write_file(const char *name, const char *data, u32 size);
int read_file(const char *name, char *buffer, u32 size);
int delete_file(const char *name);
void display_file_names();

//#endif