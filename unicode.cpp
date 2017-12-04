#include <stdio.h>
#include "unistd.h"
#include <stdlib.h>

/*
0xxxxxxx
110xxxxx 10xxxxxx
1110xxxx 10xxxxxx 10xxxxxx
11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
*/

/*int     handle_umas(unsigned int *a, unsigned int c, int len)
{
    int             i;
    unsigned int    mask;
    int             offst;

    i = 0;
    offst = 0;
    mask = 255;
    while (i < 4)
        a[i++] = 0;
    i = len;
    while (i--)
    {
        a[i] = (c & mask) >> (8 * offst++);
        mask <<= 8;
    }
    i = 0;
    while (i < len)
        write(1, &a[i++], 1);
    return (len);
}

int ft_putchar_u(int c)
{
    unsigned int v2;
    unsigned int v3;
    unsigned int v4;
    unsigned int a[4];

    v2 = 49280;
    v3 = 14712960;
    v4 = 4034953344;
    if (c <= 127)
        return (handle_umas(a, c, 1));
    else if (c <= 2047)
        return (handle_umas(a, (((c & 63) | ((c & 1984) << 2)) | v2), 2));
    else if (c <= 65535)
        return (handle_umas(a, (((c & 63) | ((c & 4032) << 2) | \
                ((c & 61440) << 4)) | v3), 3));
    else if (c <= 2097151)
        return (handle_umas(a, (((c & 63) | ((c & 4032) << 2) | \
                ((c & 258048) << 4) | ((c & 1835008) << 6)) | v4), 4));
    return (0);
}*/

int ft_putchar_uni_old(int c)
{
    unsigned int v0 = 0;
    unsigned int v1 = 49280;
    unsigned int v2 = 14712960;
    unsigned int v3 = 4034953344;
    unsigned int a[4];
    int i;
    int ret = 0;

    i = 0;
    while (i < 4)
        a[i++] = 0;
    if (c <= 127)
    {
        a[0] = (int) c;
        ret = 1;
    }
    else if (c <= 2047)
    {
        v1 = ((c & 63) | ((c & 1984) << 2)) | v1;
        a[0] = (v1 & 65280) >> 8;
        a[1] = v1 & 255;
        ret = 2;
    }
    else if (c <= 65535)
    {
        v2 = ((c & 63) | ((c & 4032) << 2) | ((c & 61440) << 4)) | v2;
        a[0] = (v2 & 16711680) >> 16;
        a[1] = (v2 & 65280) >> 8;
        a[2] = v2 & 255;
        ret = 3;
    }
    else if (c <= 2097151)
    {
        v3 = ((c & 63) | ((c & 4032) << 2) | ((c & 258048) << 4) | ((c & 1835008) << 6)) | v3;
        a[0] = (v3 & 4278190080) >> 24;
        a[1] = (v3 & 16711680) >> 16;
        a[2] = (v3 & 65280) >> 8;
        a[3] = v3 & 255;
        ret = 4;
    }
    i = 0;
    while (a[i] != 0 && i < 4)
        write(1, &a[i++], 1);
    return (ret);
}

/*int main() {

    int i =0;
    int res = 0;
   /* res = ft_putchar_u(50);
    printf("\n%d\n", res);
    res = ft_putchar_u(126);
    printf("\n%d\n", res);
    res = ft_putchar_u(127);
    printf("\n%d\n", res);

    res = ft_putchar_u(128);
    printf("\n%d\n", res);


    res = ft_putchar_u(65534);
    printf("\n%d\n", res);
    res =  ft_putchar_u(65535);
    printf("\n%d\n", res);
    res = ft_putchar_u(65536);
    printf("\n%d\n", res);
    res = ft_putchar_u(80000);
    printf("\n%d\n", res);


    printf("\n%d\n", res);
    res = ft_putchar_u(65605);
    printf("\n%d\n", res);
    res = ft_putchar_u(65605);
    printf("\n%d\n", res);


    printf("NEXT BLOCK\n");

    res = 0;
    res = ft_putchar_uni_old(50);
    printf("\n%d\n", res);
    res = ft_putchar_uni_old(126);
    printf("\n%d\n", res);
    res = ft_putchar_uni_old(127);
    printf("\n%d\n", res);
    res = ft_putchar_uni_old(128);
    printf("\n%d\n", res);


    res = ft_putchar_uni_old(65534);
    printf("\n%d\n", res);
    res =  ft_putchar_uni_old(65535);
    printf("\n%d\n", res);
    res = ft_putchar_uni_old(65605);
    printf("\n%d\n", res);
    res = ft_putchar_uni_old(65605);
    printf("\n%d\n", res);


    printf("\n%d\n", res);
    res = ft_putchar_uni_old(65605);
    printf("\n%d\n", res);
    res = ft_putchar_uni_old(65605);
    printf("\n%d\n", res);*/
   /* while (i < 2097152) {
        ft_putchar_u(i);
        i+=100;
        write(1, "\n", 1);
       sleep(1);
    }
    return 0;
}*/



/*int     handle_umas(unsigned int *a, unsigned int c, int len)
{
    int             i;
    unsigned int    mask;
    int             offst;

    i = 0;
    offst = 0;
    mask = 255;
    while (i < 4)
        a[i++] = 0;
    if (len == 1)
        a[0] = c;
    else if (len == 2 && (i = len  * 8))

        //a[0] = (c & 65280) >> 8;
        //a[1] = c & 255;
    else if (len == 3 && (i = len * 8))
        while ((i -= 8))
        {
            a[i / 8] = (c & mask) >> offst++;
            mask <<= 8;
        }
        a[0] = (c & 16711680) >> 16;
        a[1] = (c & 65280) >> 8;
        a[2] = c & 255;
else if (len == 4)
i = len  * 8;
a[0] = (c & 4278190080) >> 24;
a[1] = (c & 16711680) >> 16;
a[2] = (c & 65280) >> 8;
a[3] = c & 255;
while ((i -= 8))
{
a[i / 8] = (c & mask) >> offst++;
mask <<= 8;
}
while (i < len)
write(1, &a[i++], 1);
return (len);
}*/