//
// string.h approach for the J.Molloy's kernel
// author: Alex. Cremieux
//

#ifndef STRING_H
#define STRING_H

#include "common.h"

void *memset(void *str, u8int constant, u32int number);
void *memcpy(void *str1, void *str2, u32int size);
char *strcpy(char *dest, char *src);
u32int strlen(char *str);
int strcmp(char *str1, char *str2);

#endif
