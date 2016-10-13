/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_widechar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:54 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/13 19:46:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
**	Case not handled:
**	(*c == 0)
*/

static void		justify(wint_t *c, t_fdata *fdatas)
{
	return;
	char	*str;
	int		ret;

	if (fdatas->flag & FLAG_SPACE)
		fdatas->out = ft_strconcat(fdatas->out, " ");
	if (fdatas->length == LENGTH_L)
	{
		str = ft_towstr((wchar_t *)c, &ret);
		fdatas->out = ft_strconcat(fdatas->out, str);
		ft_strdel(&str);
	}
	else
		fdatas->out = ft_strnconcat(fdatas->out, (char *)c, 1);
}

static int		unicode_length(t_fdata *fdatas, wint_t c)
{
	if (c <= MASK7)
	{
		fdatas->length = LENGTH_NONE;
		return (0);
	}
	else if (c <= MASK11)
		return (1);
	else if (c <= MASK16)
		return (2);
	else if (c <= MASK21)
		return (3);
	else if (c <= MASK26)
		return (4);
	else
		return (5);
	return (0);
}

int				print_formated_widechar(t_fdata *fdatas)
{
	wint_t	c;
	int		unicode_len;

	c = (wint_t)va_arg(*fdatas->ap, wint_t);
	unicode_len = unicode_length(fdatas, c);
	if (unicode_len < 0)
		return (-1);
	fdatas->width -= (unicode_len + 1);
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify(&c, fdatas);
	while (fdatas->width > 0)
	{
		//if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
		//	fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(&c, fdatas);
	return (0);
}
