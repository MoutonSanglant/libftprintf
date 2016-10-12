/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_unsigned.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 09:00:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void		justify_left(t_fdata *fdatas, char *str)
{
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
	while (fdatas->width-- > 0)
		fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
}

static void		justify_right(t_fdata *fdatas, char *str)
{
	while (fdatas->width-- > 0)
		fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
}

static char		*str_from_arg(va_list *ap, t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_uitoa((unsigned int)va_arg(*ap, unsigned int)));
	else if (fdatas->length & LENGTH_Z)
		return (ft_uitoa((size_t)va_arg(*ap, size_t)));
	else if (fdatas->length & LENGTH_J)
		return (ft_uitoa((uintmax_t)va_arg(*ap, uintmax_t)));
	else if (fdatas->length & LENGTH_LL)
		return (ft_uitoa((uint64_t)va_arg(*ap, uint64_t)));
	else if (fdatas->length & LENGTH_L)
		return (ft_uitoa((unsigned long int)va_arg(*ap, unsigned long int)));
	else if (fdatas->length & LENGTH_H)
		return (ft_uitoa((unsigned short int)va_arg(*ap, unsigned int)));
	else if (fdatas->length & LENGTH_HH)
		return (ft_uitoa((unsigned char)va_arg(*ap, unsigned int)));
	return (NULL);
}

void			print_formated_unsigned(va_list *ap, t_fdata *fdatas)
{
	char			*str;
	int				len;

	str = str_from_arg(ap, fdatas);
	if (str[0] == '0' && fdatas->precision == 0)
		str[0] = '\0';
	if (fdatas->precision >= 0)
		fdatas->fill_char = " ";
	len = ft_strlen(str);
	fdatas->precision = fdatas->precision - len;
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - len;
	if (fdatas->flag & FLAG_LESS)
		justify_left(fdatas, str);
	else
		justify_right(fdatas, str);
	ft_strdel(&str);
}
