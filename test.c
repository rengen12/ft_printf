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


int main(void)
{

    int res;
    //setlocale(LC_ALL, "");
    //c = '¡';
    //ft_putchar_u();
    //ft_putstr_u("¡™£¢∞§¶•ªº–≠œ∑´†¥¨ˆπ“‘ÅÍÎÏ©ÓÔ˚Ò…Æ«Ω≈ç√∫˜≤≥çå");
    //printf("¡™£¢∞§¶•ªº–≠œ∑´†¥¨ˆπ“‘ÅÍÎÏ©ÓÔ˚Ò…Æ«Ω≈ç√∫˜≤≥çå");

    res = printf("%u", -1);
    printf("\nres = %d\n", res);
    return (0);
}