/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_octal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:17 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/16 03:08:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void	conversion(void *dst, const void *src, size_t n)
{
	char		*to;
	char		*str;
	uintptr_t	value;

	value = (uintptr_t)*((uintptr_t *)src);
	str = &((char *)dst)[n - 1];
	to = (char *)dst;
	while (str >= to)
	{
		*str-- = HEX_TABLE(value % 8);
		value /= 8;
	}
	dst = (void *)str;
}

static size_t		nblen(uintptr_t value)
{
	size_t		l;

	l = 1;
	while (value /= 8)
		l++;
	return (l);
}

void			print_formated_octal(t_fdata *fdatas)
{
	uintmax_t	value;
	size_t		length;

	remove_flags(fdatas, FLAG_MORE | FLAG_SPACE);

	if ((value = va_uint(fdatas)))
	{
		length = nblen(value); // Clamp with precision ??
		write_format(&value, length, fdatas, conversion);
	}
	//else if (!(fdatas->flag & FLAG_NUMBERSIGN) && fdatas->precision == 0)
	else if (fdatas->precision == 0)
		write_format("", 0, fdatas, NULL);
	else
	{
		remove_flags(fdatas, FLAG_NUMBERSIGN);
		write_format("0", 1, fdatas, NULL);
	}
}
