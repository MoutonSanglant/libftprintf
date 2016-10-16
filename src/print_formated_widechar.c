/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_widechar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:54 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/16 02:36:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"


/*
**	6-bytes extension
**	=================
** else if (unicode_point <= MASK26)
**		bcount = 5;
** else if (unicode_point <= MASK31)
**		bcount = 6;
*/
static int		wintlen(wint_t unicode_point)
//static int		wcharlen(wchar_t unicode_point)
{
	int		bcount;

	bcount = -1;
	if (unicode_point < 0)
		return (-1);
	else if (unicode_point <= MASK7)
		bcount = 1;
	else if (unicode_point <= MASK11)
		bcount = 2;
	else if (unicode_point <= MASK16)
		bcount = 3;
	else if (unicode_point <= MASK21)
		bcount = 4;

	return (bcount);
}
static void	conversion(void *dst, const void *src, size_t n)
{
	ft_wstrcpy((char *)dst, (wchar_t *)src, n);
}

int				print_formated_widechar(t_fdata *fdatas)
{
	wint_t	c;
	//wchar_t	c;
	int		length;

	remove_flags(fdatas, FLAG_SPACE | FLAG_MORE | FLAG_NUMBERSIGN);

	fdatas->precision = -1;
	remove_flags(fdatas, FLAG_SPACE | FLAG_MORE);
	c = (wint_t)va_arg(*fdatas->ap, wint_t);
	//c = (wchar_t)va_arg(*fdatas->ap, wint_t);
	// TODO: if wintlen > 4, printf returns -1 and doesn't format'
	//length = wcharlen(c);
	length = wintlen(c);
	if (length < 0)
	{
		write_error(fdatas);
		return (-1);
	}
	write_format(&c, length, fdatas, &conversion);

	return (0);
}
