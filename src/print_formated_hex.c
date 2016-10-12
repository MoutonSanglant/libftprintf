/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 09:00:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void		justify(char *str, t_fdata *fdatas)
{
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
}

static char		*str_from_arg(va_list *ap, t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_itoa_base((unsigned int)va_arg(*ap, unsigned int), 16));
	else if (fdatas->length & LENGTH_Z)
		return (ft_itoa_base((size_t)va_arg(*ap, size_t), 16));
	else if (fdatas->length & LENGTH_J)
		return (ft_itoa_base((uintmax_t)va_arg(*ap, uintmax_t), 16));
	else if (fdatas->length & LENGTH_LL)
		return (ft_itoa_base((uint64_t)va_arg(*ap, uint64_t), 16));
	else if (fdatas->length & LENGTH_L)
		return (ft_itoa_base((unsigned long)va_arg(*ap, unsigned long), 16));
	else if (fdatas->length & LENGTH_H)
		return (ft_itoa_base((unsigned short)va_arg(*ap, unsigned int), 16));
	else if (fdatas->length & LENGTH_HH)
		return (ft_itoa_base((unsigned char)va_arg(*ap, unsigned int), 16));
	return (NULL);
}

static void		print_hex_string(t_fdata *fdatas, char *str, char specifier)
{
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

void			print_formated_hex(va_list *ap, t_fdata *fdatas,
										char specifier)
{
	char	*str;
	int		len;
	int		i;

	str = str_from_arg(ap, fdatas);
	if (str[0] == '0')
	{
		if (fdatas->precision == 0)
			str[0] = '\0';
		fdatas->flag ^= (fdatas->flag & FLAG_NUMBERSIGN)
							? FLAG_NUMBERSIGN : FLAG_ZERO;
	}
	i = -1;
	if (specifier == 'X')
		while (str[++i])
			str[i] = (char)ft_toupper(str[i]);
	len = ft_strlen(str);
	fdatas->precision = fdatas->precision - len;
	fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	fdatas->width = fdatas->width - fdatas->precision - len;
	print_hex_string(fdatas, str, specifier);
	ft_strdel(&str);
}
