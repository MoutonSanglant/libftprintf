/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_space.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:32 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 05:37:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
int		ft_isprint(int c)
{
	return (c > 31 && c < 127);
}
*/

/*
static void		justify(char c, t_fdata *fdatas)
{
	return;
	if (fdatas->flag & FLAG_SPACE)
		fdatas->out = ft_strconcat(fdatas->out, " ");
	if (ft_isprint(c))
		fdatas->out = ft_strnconcat(fdatas->out, &c, 1);
}
*/

static int		format_error(const char *format, t_fdata *fdatas)
{
	if (format[0] != '%')
	{
		if (format[0] == '\0' || format[1] == '\0')
			fdatas->flag |= FLAG_FORMAT_ERROR;
		return (1);
	}
	return (0);
}

void			print_formated_space(const char *format, t_fdata *fdatas)
{
	char	c;

	c = '%';
	if (format_error(format, fdatas))
		c = *format;
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	write_to_buffer(&c, 1, fdatas);
	/*
	if (fdatas->flag & FLAG_LESS)
		justify(c, fdatas);
	fdatas->width--;
	while (fdatas->width > 0)
	{
		//if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
		//	fdatas->out = ft_strnconcat(fdatas->out,
		//										fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(c, fdatas);
		*/
}
