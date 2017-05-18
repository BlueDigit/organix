//
// Stdlib.c approach for the J.Molloy's kernel
// author: Alex. Cremieux
//

#include "stdlib.h"

/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char *itohex(int num, char *str)
{
    int tmp = 0;
    int idx;
    int i;
    for(i = 28, idx = 0; i >= 0; i -= 4, idx++)
    {
        tmp = (num >> i) & 0xF;
        str[idx] = tmp >= 0xA ? tmp - 0xA + 'A' : tmp + '0';
    }
    return str;
}

// Implementation of itoa
char *itoa(int num, char *str, int base)
{
    if(base != 8 && base != 10 && base != 16) return str;
    if(base == 16) return itohex(num, str);

    int i = 0;
    char isNegative = 0;
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i] = '0';
        str[i++] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    i = 0;
    while (num != 0)
    {
        int rem = num % base;
        str[i] = digits[rem];
        i++;
        num /= base;
    }

    // If number is negative, append '-'
    if(isNegative) str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}
