/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_unsigned.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/16 00:53:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
static void		justify_left(t_fdata *fdatas, char *str)
{
	return;
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
	while (fdatas->width-- > 0)
		fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
}

static void		justify_right(t_fdata *fdatas, char *str)
{
	return;
	while (fdatas->width-- > 0)
		fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
}
*/

/*
static char		*str_from_arg(t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_uitoa((unsigned int)va_arg(*fdatas->ap, unsigned int)));
	else if (fdatas->length & LENGTH_Z)
		return (ft_uitoa((size_t)va_arg(*fdatas->ap, size_t)));
	else if (fdatas->length & LENGTH_J)
		return (ft_uitoa((uintmax_t)va_arg(*fdatas->ap, uintmax_t)));
	else if (fdatas->length & LENGTH_LL)
		return (ft_uitoa((uint64_t)va_arg(*fdatas->ap, uint64_t)));
	else if (fdatas->length & LENGTH_L)
		return (ft_uitoa((unsigned long int)va_arg(*fdatas->ap, unsigned long int)));
	else if (fdatas->length & LENGTH_H)
		return (ft_uitoa((unsigned short int)va_arg(*fdatas->ap, unsigned int)));
	else if (fdatas->length & LENGTH_HH)
		return (ft_uitoa((unsigned char)va_arg(*fdatas->ap, unsigned int)));
	return (NULL);
}
*/

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
		*str-- = HEX_TABLE(value % 10);
		value /= 10;
	}
	dst = (void *)str;
}

static size_t		nblen(uintptr_t value)
{
	size_t		l;

	l = 1;
	while (value /= 10)
		l++;
	return (l);
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
