//
// string.h approach for the J.Molloy's kernel
// author: Alex. Cremieux
//

#include "string.h"
#include "common.h"
#include "kheap.h"

void *memset(void *str, u8int constant, u32int number)
{
    char *c = (char*)str;
    for(u32int idx = 0; idx < number; idx++)
    {
        c[idx] = constant;
    }
    return str;
}


void *memcpy(void *dest, void *src, u32int size)
{
    char *cdest = (char *)dest;
    char *csrc = (char *)src;
    u32int i = 0;
    for(i = 0; i < size; i++)
    {
        cdest[i] = csrc[i];
    }
}

char *strcpy(char *dest, char *src)
{
    u32int i = 0;
    while(src[i] != '\n')
    {
        dest[i] = src[i];
    }
    return dest;
}

u32int strlen(char *str)
{
    u32int len = 0;
    while(str[len] != '\n')
    {
        len++;
    }
    return len;
}

int strcmp(char *str1, char *str2)
{
    int output = 1;
    int i = 0;
    while(str1[i] != '\n' && output){
        output = str1[i] == str2[i];
        i++;
    }
    return output ? str1[i] == str2[i] : 0;
}
