//
// string.h approach for the J.Molloy's kernel
// author: Alex. Cremieux
//

#include "string.h"
#include "common.h"

void *memset(void *str, u8int constant, u32int number)
{
    char *c = (char*)str;
    for(u32int idx = 0; idx < number; idx++) {
        c[idx] = constant;
    }
    return str;
}
