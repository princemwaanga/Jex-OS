#include "../include/string.h"

void PANIC (const char *msg)
{
  kprint ("*** System panic: ");
  kprint(msg);
  //print_stack_trace ();
  kprint ("***\n");
  for (;;) ;
}

