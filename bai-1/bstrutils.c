#include <stdio.h>
#include "strutils.h"

#define MIN_LEN_INPUT_2_STRING 3

int len(char string[]){
    int i = 0;
    while (string[i] != NULL) {
        i++;
    }
    return i;
}

void cpy_char(char in[], char out[], int start) {
    int i = start;
    int j = 0;
    while (in[i] != '\0') {
        out[j] = in[i];
        i++; j++;
    }
    out[j] = '\0'; 
}

void str_reverse(char string[], char string_out[], int STR_LEN) {
    cpy_char(string, string_out, 0);
    char temp = 0;
    for (int i = 0; i <  STR_LEN / 2;i++) {
        temp = string_out[i];
        string_out[i] = string_out[STR_LEN - i - 1];
        string_out[STR_LEN - 1 - i] = temp;
    }
}

void str_trim(char string[], char string_out[], int STR_LEN) {
    char rpl[50];
    cpy_char(string, string_out, 0);
    for (int i = 0; i <  STR_LEN;i++) {
        if (string_out[i] != ' ') {
            cpy_char(string_out, rpl, i);
            STR_LEN -= i;
            break;    
        }
    }
    for (int i = STR_LEN - 1; i >= 0; i--) {
        if (rpl[i] != ' '){ 
            rpl[i + 1] = '\0';
            break;    
        }  
    }
    cpy_char(rpl, string_out, 0);
} 

int power(int num, int order) {
    int ret = 1;
    for (int i = 0; i < order; i++) {
        ret *= 10;
    }
    return ret;
}

int char_to_digit (char char_) {
    if (char_ == ' ') 
        return -2;
    else if (char_ >= '0' && char_ <= '9')
        return char_ - '0';
    else if (char_ == '-')
        return -1;
    else
        return -3; 
}

int check_error(char in[]) {
    int i = 0;
    if (char_to_digit(in[0] == -1))
        i = 1;
    while (in[i] != '\0') {
        if (char_to_digit(in[i]) == -3) {
            return 1;
        } 
        i++;
    }
    if (len(in) >= MIN_LEN_INPUT_2_STRING) {
        i = 0;
        while (in[i] != '\0') {
            if (in[i - 1] != ' ' && in[i] == ' ') { 
                return 0;
            } 
            i++;
        }
        return 2;
    } 
}

int str_to_int_no_dbg (char string[]) {
    int int_out = 0;
    char rev_str[50];
    int traverse_len = len(string);
    str_reverse(string, rev_str, len(string));
    if (char_to_digit(string[0]) == -1)
        traverse_len = len(string) - 1;
    for (int i = 0;i < traverse_len; i++) {
        int_out += char_to_digit(rev_str[i]) * power(10, i);
    }
    if (char_to_digit(string[0]) == -1)
        int_out = -int_out;
    return int_out;
}

int str_to_int (char string[], int message[]) {
    char string_out[50];
    str_trim(string, string_out, len(string));
    switch (check_error(string_out)) {
        case 0:
            message[0] = 0;
            break; 
        case 1:
            message[0] = 1;
            break;
        case 2:
            message[0] = 2; message[1] = str_to_int_no_dbg(string_out); 
            break;
    }
}