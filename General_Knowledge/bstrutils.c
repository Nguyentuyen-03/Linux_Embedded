#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "strutils.h"

void str_trim(char *str) {
    char *start = str;
    while (isspace(*start)) start++;

    char *end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) end--;

    *(end + 1) = '\0';
    memmove(str, start, end - start + 2);
}


void str_reverse(char *str) {
    char tmp;
    int len = strlen(str);

    for (int i = 0; i < len / 2; ++i) {
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }

}


int str_to_int(const char *str, int *out_num) {
    
    if (*str == '\0') return 0;

    char *endptr;
    long result = strtol(str, &endptr, 10);

    if (*endptr != '\0') return 0;

    *out_num = (int)result;
    return 1;
}

