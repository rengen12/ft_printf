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

int		main(void)
{
	int res;

	res = printf("{%05.S}", L"42 c est cool");
	//printf("\nres = %d", res);
	//printf("Le fichier{cyan}%s{eoc} contient : {red}%s{eoc}", "filename", "str");
	return (0);
}