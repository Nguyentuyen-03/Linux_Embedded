#include <stdio.h>
#include "strutils.h"

int main() {

    int num;
    char str1[] = "  Hello Tuyen  ";
    char str2[] = "abcxyz";
    char str3[] = "123";


    str_trim(str1);
    printf("str1 sau khi xoa: '%s'\n", str1);

    str_reverse(str2);
    printf("str2 sau khi dao: '%s'\n", str2);

    if (str_to_int(str3, &num)) {
        printf("Chuyen '%s' thanh %d\n", str3, num);
    } else {
        printf("Loi chuyen '%s'\n", str3);
    }

    return 0;
}
