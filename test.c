/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:24:00 by amichak           #+#    #+#             */
/*   Updated: 2017/11/23 18:24:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "ft_printf.h"
//#include <locale.h>
//#include <wchar.h>

char *push_char(char *mas, char ch, int max)
{
    size_t i;

    i = 0;
    while (i < max)
    {
        if (!mas[i])
        {
            mas[i] = ch;
            break ;
        }
        i++;
    }
    return (mas);
}

void movep(char **a)
{
    ft_putchar(*(*a)++);
    int b;
    b = 1;
    b++;
    a++;
}

int main(void) {

    int res;
    //setlocale(LC_ALL, "");
    //c = '¡';
    //ft_putchar_u();
    //ft_putstr_u("¡™£¢∞§¶•ªº–≠œ∑´†¥¨ˆπ“‘ÅÍÎÏ©ÓÔ˚Ò…Æ«Ω≈ç√∫˜≤≥çå");
    //printf("¡™£¢∞§¶•ªº–≠œ∑´†¥¨ˆπ“‘ÅÍÎÏ©ÓÔ˚Ò…Æ«Ω≈ç√∫˜≤≥çå");


   /* char *a;

    a = ft_strnew(100);

    push_char(a, 97, 100);
    push_char(a, 98, 100);
    push_char(a, 99, 100);
    push_char(a, 100, 100);
    push_char(a, 101, 100);
    push_char(a, 102, 100);

    ft_putendl(a);

    movep(&a);
    ft_putendl(a);*/
    //ft_printf("fdsfsf %llszkoop", "123456");
    /*int var = -42;
    res = ft_printf("%X", var);
    printf("\nres = %d\n", res);*/


int *test;
    ft_printf("");
    ft_printf("\\n");
    ft_printf("test");
    ft_printf("test\\n");
   ft_printf("1234");
    ft_printf("%%");
    ft_printf("%5%");
   ft_printf("%-5%");
    ft_printf("%.0%");
    ft_printf("%%", "test");
    ft_printf("%   %", "test");
    ft_printf("%x", 42);
    ft_printf("%X", 42);
    ft_printf("%x", 0);
    ft_printf("%X", 0);
    ft_printf("\n");
    ft_printf("%x", -42);
    ft_printf("%X", -42);
    ft_printf("%x", 4294967296);
    ft_printf("%X", 4294967296);
    ft_printf("%x", test);
    ft_printf("%10x", 42);
    ft_printf("%-10x", 42);
    ft_printf("%lx", 4294967296);
    ft_printf("%llX", 4294967296);
    ft_printf("%hx", 4294967296);
    ft_printf("%hhX", 4294967296);
    ft_printf("%jx", 4294967295);

    return (0);
}