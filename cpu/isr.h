#include "types.h"

/* Struct which aggregates many registers */
typedef struct {
   u32 ds; /* Data segment selector */
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
   u32 int_no, err_code; /* Interrupt number and error code (if applicable) */
   u32 eip, cs, eflags, useresp, ss; /* Pushed by the processor automatically */
} registers_t;

void isr_install();
void isr_handler(registers_t r);

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(u8 n, isr_t handler);