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
	int res1, res2;
	//char* l = setlocale(LC_ALL, "");

	//long double ld = DBL_MAX;
	//res = ft_printf("%LF\n ", ld);
	/*res = ft_printf("%C", L'ø');
	printf("\nres = %d\n", res);
	res = printf("%C", L'ø');
	printf("\nres = %d\n", res);*/
	/*char *a = "ø";
	char *b = L'ø';

	size_t a1 = (size_t)*a;
	size_t b1 = (size_t)b;*/

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
	long double ld = 32424.235;
	res1 = ft_printf("%LE", ld);
	ft_printf("\nmy res = %d\n", res1);
	res1 = ft_printf("%C", L'й');
	ft_printf("\nmy res = %d\n", res1);

	/*res2 = printf("%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C \
%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C\
%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C%C\n",
				  ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-',
				  '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';',
				  '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
				  'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
				  'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e',
				  'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
				  't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}');*/
	//ft_printf("my res = %d ", res1);
	//ft_printf("unix res = %d\n\n", res2);
	//ft_printf("{red}");

	//write(1, b, ft_strlen(b));
	//printf("Le fichier{cyan}%s{eoc} contient : {red}%s{eoc}", "filename", "str");
	return (0);
}