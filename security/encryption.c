#include "encryption.h"

char* encode(char* str) {

    char *original = str;  

    while (*str) {
        *str = (*str + 3) % 128;  
        str++;
    }

    return original;

}

char* decode(char* str) {

    char *original = str;  

    while (*str) {
        *str = (*str - 3 + 128) % 128;  
        str++;
    }

    return original;

}