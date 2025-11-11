#ifndef strutils
#define strutils
int len(char string[]);
void str_reverse( char string[], char string_out[],int STR_LEN);
void str_trim(char string[], char string_out[], int STR_LEN);
void cpy_char(char in[], char out[], int start);
int str_to_int (char string[], int message[]);
#endif
