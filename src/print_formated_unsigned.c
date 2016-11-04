/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_unsigned.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/04 04:30:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static size_t		nblen(uintptr_t value)
{
	size_t		l;

	l = 1;
	while (value /= 10)
		l++;
	return (l);
}

static void	conversion(void *dst, const void *src, size_t n)
{
	char		*to;
	char		*str;
	uintptr_t	value;
	int			l;

	value = (uintptr_t)*((uintptr_t *)src);
	l = nblen(value) - 1;
	while (l-- >= (int)n)
		value /= 10;
	str = &((char *)dst)[n - 1];
	to = (char *)dst;
	while (str >= to)
	{
		*str-- = HEX_TABLE(value % 10);
		value /= 10;
	}
	dst = (void *)str;
}

void			print_formated_unsigned(t_fdata *fdatas)
{
	uintmax_t	value;
	size_t		length;

	remove_flags(fdatas, FLAG_SPACE | FLAG_MORE | FLAG_NUMBERSIGN);

	if ((value = va_uint(fdatas)))
	{
		length = nblen(value); // Clamp with precision ??
		write_format(&value, length, fdatas, conversion);
	}
	else if (!(fdatas->flag & FLAG_NUMBERSIGN) && fdatas->precision == 0)
		write_format("", 0, fdatas, NULL);
	else
		write_format("0", 1, fdatas, NULL);

	/*
	char			*str;
	int				len;

	str = str_from_arg(fdatas);
	if (str[0] == '0' && fdatas->precision == 0)
		str[0] = '\0';
	if (fdatas->precision >= 0)
		fdatas->fill_char = " ";
	len = ft_strlen(str);
	write_format(str, ft_strlen(str), fdatas, NULL);
	*/
	/*
	fdatas->precision = fdatas->precision - len;
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - len;
	if (fdatas->flag & FLAG_LESS)
		justify_left(fdatas, str);
	else
		justify_right(fdatas, str);
		*/
	//ft_strdel(&str);
}
