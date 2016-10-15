/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/15 00:12:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
static void		justify(char *str, t_fdata *fdatas)
{
	return;
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
}
*/


/*
static void		print_hex_string(t_fdata *fdatas, char *str, char specifier)
{
	return;
	if (fdatas->flag & FLAG_NUMBERSIGN)
	{
		fdatas->width -= 2;
		if (fdatas->flag & FLAG_ZERO)
			fdatas->out = ft_strconcat(fdatas->out, HEX_CHECK(specifier));
	}
	if (fdatas->flag & FLAG_LESS)
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->out = ft_strconcat(fdatas->out, HEX_CHECK(specifier));
		justify(str, fdatas);
	}
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE || fdatas->flag & FLAG_SPACE)
				|| fdatas->width > 1)
			fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->out = ft_strconcat(fdatas->out, HEX_CHECK(specifier));
		justify(str, fdatas);
	}
}
*/

/*
** Write numbers backward then write '0x' forward
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
		*str-- = HEX_TABLE(value % 16);
		value /= 16;
	}
	dst = (void *)str;
}

static void	conversion_prefixed(void *dst, const void *src, size_t n)
{
	char		*to;
	char		*str;
	uintptr_t	value;

	value = (uintptr_t)*((uintptr_t *)src);
	str = &((char *)dst)[n - 1];
	to = (char *)dst;
	while (str > to)
	{
		*str-- = HEX_TABLE(value % 16);
		value /= 16;
	}
	*str++ = '0';
	*str++ = 'x';
	dst = (void *)str;
}

static void	conversion_upper(void *dst, const void *src, size_t n)
{
	char		*to;
	char		*str;
	uintptr_t	value;

	value = (uintptr_t)*((uintptr_t *)src);
	str = &((char *)dst)[n - 1];
	to = (char *)dst;
	while (str >= to)
	{
		*str-- = HEX_TABLE_UPPER(value % 16);
		value /= 16;
	}
	dst = (void *)str;
}

static void	conversion_upper_prefixed(void *dst, const void *src, size_t n)
{
	char		*to;
	char		*str;
	uintptr_t	value;

	value = (uintptr_t)*((uintptr_t *)src);
	str = &((char *)dst)[n - 1];
	to = (char *)dst;
	while (str > to)
	{
		*str-- = HEX_TABLE_UPPER(value % 16);
		value /= 16;
	}
	*str++ = '0';
	*str++ = 'X';
	dst = (void *)str;
}

static size_t		nblen(uintptr_t value)
{
	size_t		l;

	l = 1;
	while (value /= 16)
		l++;
	return (l);
}

void			print_formated_hex(t_fdata *fdatas, char specifier)
{
	uintmax_t	value;
	size_t		length;
	void		(*conversion_fn)(void *, const void *, size_t);

	if ((value = va_uint(fdatas)))
	{
		length = nblen(value);
		if ((fdatas->flag & FLAG_NUMBERSIGN))
		{
			length += 2;
			conversion_fn = (specifier == 'X') ? &conversion_upper_prefixed : &conversion_prefixed;
		}
		else
			conversion_fn = (specifier == 'X') ? &conversion_upper : &conversion;
		write_format(&value, length, fdatas, conversion_fn);
	}
	else if (fdatas->precision == 0)
		write_format("", 0, fdatas, NULL);
	else
		write_format("0", 1, fdatas, NULL);
}
