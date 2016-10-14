/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 22:59:46 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void		remove_extra_flags(t_fdata *fdatas)
{
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_ZERO)
		fdatas->flag |= FLAG_LESS;
}

/*
** Write numbers backward then write '0x' forward
*/
/*
static void	conversion(void *dst, const void *src, size_t n)
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

static size_t		nblen(uintptr_t value)
{
	size_t		l;

	l = 1;
	while (value /= 16)
		l++;
	return (l + 2);
}
*/

void			print_formated_pointer(t_fdata *fdatas)
{
	remove_extra_flags(fdatas);
	fdatas->length = LENGTH_LL;
	fdatas->flag |= FLAG_NUMBERSIGN;
	print_formated_hex(fdatas, 'x');
	/*
	uintptr_t	value;

	value = va_arg(*fdatas->ap, uintptr_t);
	remove_extra_flags(fdatas);
	if (value)
		write_format(&value, nblen(value), fdatas, &conversion);
	else if (fdatas->precision == 0)
		write_format("", 0, fdatas, NULL);
	else
		write_format("0", 1, fdatas, NULL);
		*/
	/*
	fdatas->precision -= ft_strlen(s) + 1;
	while (fdatas->precision >= 0)
	{
		join = ft_strjoin("0", s);
		ft_strdel(&s);
		s = join;
		fdatas->precision--;
		fdatas->width--;
	}
	join = ft_strjoin("0x", s);
	*/
	//write_format(s, ft_strlen(s), fdatas, &conversion);
	//print_formated_string(fdatas, join);
	//ft_strdel(&s);
	//ft_strdel(&join);
}
