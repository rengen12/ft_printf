/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:28:00 by amichak           #+#    #+#             */
/*   Updated: 2017/12/26 20:28:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

int		ft_putstr_col_code(char const *s)
{
	if (!s)
		return (0);
	write(1, s, ft_strlen(s));
	return (1);
}

int		parse_col_mcwu(char const *t)
{
	if (!ft_strcmp(t, "magenta"))
	{
		if (!ft_strcmp(t, "magenta_bg}"))
			return (ft_putstr_col_code(MAGENTA_BG));
		else if (!ft_strcmp(t, "magenta}"))
			return (ft_putstr_col_code(MAGENTA));
	}
	else if (!ft_strcmp(t, "cyan"))
	{
		if (!ft_strcmp(t, "cyan_bg}"))
			return (ft_putstr_col_code(CYAN_BG));
		else if (!ft_strcmp(t, "cyan}"))
			return (ft_putstr_col_code(CYAN));
	}
	else if (!ft_strcmp(t, "white"))
	{
		if (!ft_strcmp(t, "white_bg}"))
			return (ft_putstr_col_code(WHITE_BG));
		else if (!ft_strcmp(t, "white}"))
			return (ft_putstr_col_code(WHITE));
	}
	else if (!ft_strcmp(t, "underline}"))
		return (ft_putstr_col_code(UNDERLINE));
	return (0);
}

int		parse_col_ergy(char const *t)
{
	if (!ft_strcmp(t, "eoc}"))
		return (ft_putstr_col_code(EOC));
	else if (!ft_strcmp(t, "red"))
	{
		if (!ft_strcmp(t, "red_bg}"))
			return (ft_putstr_col_code(RED_BG));
		else if (!ft_strcmp(t, "red}"))
			return (ft_putstr_col_code(RED));
	}
	else if (!ft_strcmp(t, "green"))
	{
		if (!ft_strcmp(t, "green_bg}"))
			return (ft_putstr_col_code(GREEN_BG));
		else if (!ft_strcmp(t, "green}"))
			return (ft_putstr_col_code(GREEN));
	}
	else if (!ft_strcmp(t, "yellow"))
	{
		if (!ft_strcmp(t, "yellow_bg}"))
			return (ft_putstr_col_code(YELLOW_BG));
		else if (!ft_strcmp(t, "yellow}"))
			return (ft_putstr_col_code(YELLOW));
	}
	return (0);
}

int		parse_col_bi(char const *t)
{
	if (!ft_strcmp(t, "blue"))
	{
		if (!ft_strcmp(t, "blue_bg}"))
			return (ft_putstr_col_code(BLUE_BG));
		else if (!ft_strcmp(t, "{blue}"))
			return (ft_putstr_col_code(BLUE));
	}
	else if (!ft_strcmp(t, "black"))
	{
		if (!ft_strcmp(t, "black_bg}"))
			return (ft_putstr_col_code(BLACK_BG));
		else if (!ft_strcmp(t, "{black}"))
			return (ft_putstr_col_code(BLACK));
	}
	else if (!ft_strcmp(t, "bold}"))
		return (ft_putstr_col_code(BOLD));
	else if (!ft_strcmp(t, "blink}"))
		return (ft_putstr_col_code(BLINK));
	else if (!ft_strcmp(t, "italic}"))
		return (ft_putstr_col_code(ITALIC));
	else if (!ft_strcmp(t, "inverted}"))
		return (ft_putstr_col_code(INVERTED));
	else if (!ft_strcmp(t, "invisible}"))
		return (ft_putstr_col_code(INVISIBLE));
	return (0);
}

void	parse_color(char const **s)
{
	(*s)++;
	if (parse_col_ergy(*s) || parse_col_mcwu(*s) || parse_col_bi(*s))
	{
		*s = ft_strchr(*s, '}') + 1;
		if (**s == '{')
			parse_color(s);
	}
	else
		(*s)--;
}
