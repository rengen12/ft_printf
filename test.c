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
#include <locale.h>
//#include <wchar.h>

/*
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
*/
/**
 *
 * L and unlim double
 *
 * a g e
 * ' $
 * cleaning
 * ilon mask
 */

int 	char_size(size_t ch)
{
	int 	i;

	i = 0;
	while (ch)
	{
		ch >>= 1;
		i++;
	}
	return (i);
}

int		main(void)
{
	int res;
	//char* l = setlocale(LC_ALL, "");

	//long double ld = DBL_MAX;
	//res = ft_printf("%LF\n ", ld);
	/*res = ft_printf("%C", L'ø');
	printf("\nres = %d\n", res);
	res = printf("%C", L'ø');
	printf("\nres = %d\n", res);*/
	char *a = "ø";
	char *b = L'ø';

	size_t a1 = (size_t)*a;
	size_t b1 = (size_t)b;

	/*int i = 0;
	while (i < 300) {
		res = printf("%C", i);
		printf("\nres = %d\n", res);
		res = ft_printf("%C", i);
		printf("\nres = %d\n", res);
		printf("i = %d\n\n", i);
		i++;
	}*/

	//res = printf("%e", 3.65);
	res = ft_printf("%x", 3.65);
	//res = ft_printf("%C %d", 945, MB_CUR_MAX); //цукенг
	printf("\nres = %d\n", res);
	//ft_printf("{red}");

	//write(1, b, ft_strlen(b));
	//printf("Le fichier{cyan}%s{eoc} contient : {red}%s{eoc}", "filename", "str");
	return (0);
}