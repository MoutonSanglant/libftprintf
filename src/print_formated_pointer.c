/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/13 18:08:15 by tdefresn         ###   ########.fr       */
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

void			print_formated_pointer(t_fdata *fdatas)
{
	char	*str;
	char	*s;
	char	*join;

	str = va_arg(*fdatas->ap, char *);
	if (str)
		s = ft_itoa_base((uintptr_t)str, 16);
	else if (fdatas->precision == 0)
		s = ft_strdup("");
	else
		s = ft_strdup("0");
	remove_extra_flags(fdatas);
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
	print_formated_string(fdatas, join);
	ft_strdel(&s);
	ft_strdel(&join);
}
