#include <iostream>
#include <stdio.h>
#include "unistd.h"
#include <stdlib.h>

/*
0xxxxxxx
110xxxxx 10xxxxxx
1110xxxx 10xxxxxx 10xxxxxx
11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

void ft_putchar_uni(int c)
{
    unsigned int v0 = 0;
    unsigned int v1 = 49280;
    unsigned int v2 = 14712960;
    unsigned int v3 = 4034953344;
    unsigned int a[4];
    int i;

    i = 0;
    while (i < 4)
        a[i++] = 0;
    if (c <= 127)
        a[0] = (int)c;
    else if (c <= 2047)
    {
        v1 = ((c & 63) | ((c & 1984) << 2)) | v1;
        a[0] = (v1 & 65280) >> 8;
        a[1] = v1 & 255;
    }
    else if (c <= 65535)
    {
        v2 = ((c & 63) | ((c & 4032) << 2) | ((c & 61440) << 4)) | v2;
        a[0] = (v2 & 16711680) >> 16;
        a[1] = (v2 & 65280) >> 8;
        a[2] = v2 & 255;
    }
    else if (c <= 2097151)
    {
        v3 = ((c & 63) | ((c & 4032) << 2) | ((c & 258048) << 4) | ((c & 1835008) << 6)) | v3;
        a[0] = (v3 & 4278190080) >> 24;
        a[1] = (v3 & 16711680) >> 16;
        a[2] = (v3 & 65280) >> 8;
        a[3] = v3 & 255;
    }
    i = 0;
    while (a[i] != 0 && i < 4)
        write(1, &a[i++], 1);
}

int main() {



   //setlocale(LC_ALL, "");

    /*if (l == NULL)
    {
        printf("Locale not set\n");
    }
    else
    {
        *l = '0x04';
        *(l+1) = '0x11';
        printf("Locale set to %s\n", l);
    }
    printf("%s", 0x0411);*/


    /*int a[2];
    a[0] = 206;
    a[1] = 177;
    write(1, &(a[0]), 1);
    write(1, &(a[1]), 1);*/
    int i =0;
    ft_putchar_uni(20000);
   /*while (i < 2097152) {
        ft_putchar_uni(i);
        i += 100;
        write(1, "\n", 1);
       //sleep(1);
    }*/
    return 0;
}