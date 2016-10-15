/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_digit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:45:59 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/15 22:45:37 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void	conversion(void *dst, const void *src, size_t n)
{
	char		*to;
	char		*str;
	intptr_t	value;
	int			sign;

	value = (intptr_t)*((intptr_t *)src);
	sign = (value < 0) ? 1 : 0;
	str = &((char *)dst)[n - 1];
	to = (char *)dst;
	while (str >= to)
	{
		*str-- = (sign > 0) ? HEX_TABLE(-(value % 10)) : HEX_TABLE(value % 10);
		value /= 10;
	}
	dst = (void *)str;
}

static size_t		nblen(intptr_t value)
{
	size_t		l;

	l = 1;
	while (value /= 10)
		l++;
	return (l);
}

void			print_formated_digit(t_fdata *fdatas)
{
	intmax_t	value;
	size_t		length;

	if ((value = va_int(fdatas)))
	{
		length = nblen(value);
		if (value < 0)
			fdatas->flag |= FLAG_NEGATIVE;
		write_format(&value, length, fdatas, conversion);
	}
	else if (fdatas->precision == 0)
		write_format("", 0, fdatas, NULL);
	else
		write_format("0", 1, fdatas, NULL);
}
