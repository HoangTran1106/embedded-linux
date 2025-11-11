#include <stdio.h>
#include "strutils.h"


int main () {
    char string[50];
    char string_out[50];    
    int message[] = {3,3}; 
    printf("Enter the string: ");
    scanf("%[^\n]s", string); 
    const int STR_LEN = len(string);
    str_reverse(string, string_out, STR_LEN);
    printf("Reverse: \"%s\"\n", string_out);
    str_trim(string, string_out, STR_LEN);
    printf("Trim: \"%s\"\n", string_out);
    str_to_int(string, message);
    printf("%d\n", message[0]);
    if (message[0] == 0)
        printf("More than 1 string detected !! Enter 1 string only !!\n");
    else if (message[0] == 1)
        printf("String include alphabet or special character!! Enter integer only !!\n");
    else if (message[0] == 2)
        printf("String to int: %d\n", message[1]);
}


