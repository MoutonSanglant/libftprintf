/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_widechar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:54 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 21:17:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
**	Case not handled:
**	(*c == 0)
*/

static int		wintlen(wint_t unicode_point)
{
	int		bcount;

	bcount = 6;
	if (unicode_point <= MASK7)
		bcount = 1;
	else if (unicode_point <= MASK11)
		bcount = 2;
	else if (unicode_point <= MASK16)
		bcount = 3;
	else if (unicode_point <= MASK21)
		bcount = 4;
	else if (unicode_point <= MASK26)
		bcount = 5;
	return (bcount);
}
static void	conversion(void *dst, const void *src, size_t n)
{
	ft_wstrcpy((char *)dst, (wchar_t *)src, n);
}

int				print_formated_widechar(t_fdata *fdatas)
{
	wint_t	c;

	c = (wint_t)va_arg(*fdatas->ap, wint_t);
	write_format(&c, wintlen(c), fdatas, &conversion);

	return (0);
}
