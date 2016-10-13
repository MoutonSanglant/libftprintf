/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:45:50 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/13 19:44:29 by tdefresn         ###   ########.fr       */
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
	if (fdatas->flag & FLAG_SPACE)
		fdatas->out = ft_strconcat(fdatas->out, " ");
	else
		fdatas->out = ft_strnconcat(fdatas->out, (char *)c, 1);
}

int				print_formated_char(t_fdata *fdatas)
{
	wint_t	c;

	c = 0;
	if (fdatas->length == LENGTH_NONE)
		c = (wint_t)va_arg(*fdatas->ap, int);
	else if (fdatas->length == LENGTH_L)
	{
		if (print_formated_widechar(fdatas) < 0)
			return (-1);
		return (0);
	}
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify(&c, fdatas);
	fdatas->width--;
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
