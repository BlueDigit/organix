//
// Stdlib.c approach for the J.Molloy's kernel
// author: Alex. Cremieux
//

#include "monitor.h"

// for now, it manage ontly positive numbers
char *itoa(int val, char *str, int base)
{
    char digits[] = {'0','1','2','3','4','5','6','7','8','9',
                    'A','B','C','D','E','F'};

    if(base > 0 && base <= 16) {

        int temp = val;
        int idx  = 0;

        while(temp > 0) {
            int digit = temp % base;
            str[idx]  = digits[digit];
            temp = temp / base;
            idx++;
        }

        str[idx] = '\0';
        int end = idx - 1;
        idx = 0;
        
        while(idx < end) {
            char temp = str[idx];
            str[idx]  = str[end];
            str[end]  = temp;
            temp--;
            idx++;
        }
    }

    return str;
}
