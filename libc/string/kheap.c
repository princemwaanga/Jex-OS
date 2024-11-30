#include "../../cpu/types.h"

/* This should be computed at link time, but a hardcoded
 * value is fine for now. Remember that our kernel starts
 * at 0x1000 as defined on the Makefile */
u32 placement_address = 0x10000;
/* Implementation is just a pointer to some free memory which
 * keeps growing */

u32 kmalloc(u32 size)
{
    u32 temp = placement_address;
    placement_address += size;
    return temp;
}

u32 kmalloc_p(u32 size, /*u32 *phys*/ int align) // returns a physical address
{
    if(align == 1 && (placement_address & 0xFFFFF000))
    {
        //Align it
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    u32 tmp = placement_address;
    placement_address += size;
    return tmp;
}

u32 kmalloc_ap(u32 size,int align, u32 *phys) //for fork()ing processes
{
    if(align == 1 && (placement_address & 0xFFFFF000))
    {
        //Align it
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if(phys)
    {
        *phys = placement_address;
    }
    u32 tmp = placement_address;
    placement_address += size;
    return tmp;
}
