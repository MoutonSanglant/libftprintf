/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_octal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:17 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 20:34:42 by tdefresn         ###   ########.fr       */
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

static char		*str_from_arg(t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_itoa_base(va_arg(*fdatas->ap, unsigned int), 8));
	else if (fdatas->length & LENGTH_Z)
		return (ft_itoa_base((size_t)va_arg(*fdatas->ap, size_t), 8));
	else if (fdatas->length & LENGTH_J)
		return (ft_itoa_base((uintmax_t)va_arg(*fdatas->ap, uintmax_t), 8));
	else if (fdatas->length & LENGTH_LL)
		return (ft_itoa_base((uint64_t)va_arg(*fdatas->ap, uint64_t), 8));
	else if (fdatas->length & LENGTH_L)
		return (ft_itoa_base((unsigned long)va_arg(*fdatas->ap, unsigned long), 8));
	else if (fdatas->length & LENGTH_H)
		return (ft_itoa_base((unsigned short int)va_arg(*fdatas->ap, unsigned int), 8));
	else if (fdatas->length & LENGTH_HH)
		return (ft_itoa_base((unsigned char)va_arg(*fdatas->ap, unsigned int), 8));
	return (NULL);
}

/*
static void		printf_octal_string(t_fdata *fdatas, char *str)
{
	return;
	if (fdatas->flag & FLAG_NUMBERSIGN)
	{
		fdatas->width--;
		if (fdatas->flag & FLAG_ZERO)
			fdatas->out = ft_strconcat(fdatas->out, "0");
	}
	if (fdatas->flag & FLAG_LESS)
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->out = ft_strconcat(fdatas->out, "0");
		justify(str, fdatas);
	}
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE
					|| fdatas->flag & FLAG_SPACE) || fdatas->width > 1)
			fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
	{
		if (fdatas->flag & FLAG_NUMBERSIGN && !(fdatas->flag & FLAG_ZERO))
			fdatas->out = ft_strconcat(fdatas->out, "0");
		justify(str, fdatas);
	}
}
*/

void			print_formated_octal(t_fdata *fdatas)
{
	char	*str;
	int		len;

	str = str_from_arg(fdatas);
	if (str[0] == '0'
			&& (fdatas->precision == 0 || fdatas->flag & FLAG_NUMBERSIGN))
		str[0] = '\0';
	//if (fdatas->flag & FLAG_NUMBERSIGN)
	//	fdatas->precision--;
	len = ft_strlen(str);
	write_format(str, len, fdatas, NULL);
	/*
	fdatas->precision = fdatas->precision - len;
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - len;
	printf_octal_string(fdatas, str);
	*/
	ft_strdel(&str);
}
