/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_digit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:45:59 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 09:00:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void		print_prefixes(char **str, t_fdata *fdatas)
{
	if ((*str)[0] == '-')
	{
		(*str)++;
		fdatas->out = ft_strconcat(fdatas->out, "-");
		fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	}
	else if (fdatas->flag & FLAG_MORE)
		fdatas->out = ft_strconcat(fdatas->out, "+");
	else if (fdatas->flag & FLAG_SPACE)
		fdatas->out = ft_strconcat(fdatas->out, " ");
}

static void		justify_left(t_fdata *fdatas, char *str)
{
	if (str[0] == '-' || (fdatas->flag & (FLAG_MORE | FLAG_SPACE)))
		print_prefixes(&str, fdatas);
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
	while (fdatas->width-- > 0)
		fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
}

static void		justify_right(t_fdata *fdatas, char *str)
{
	if (fdatas->flag & FLAG_ZERO)
	{
		if (str[0] == '-' || (fdatas->flag & (FLAG_MORE | FLAG_SPACE)))
			print_prefixes(&str, fdatas);
		while (fdatas->width-- > 0)
			fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
	}
	else
	{
		while (fdatas->width-- > 0)
			fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
		if (str[0] == '-' || (fdatas->flag & (FLAG_MORE | FLAG_SPACE)))
			print_prefixes(&str, fdatas);
	}
	while (fdatas->precision-- > 0)
		fdatas->out = ft_strconcat(fdatas->out, "0");
	fdatas->out = ft_strconcat(fdatas->out, str);
}

static char		*str_from_arg(va_list *ap, t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_itoa(va_arg(*ap, int)));
	else if (fdatas->length & LENGTH_Z)
		return (ft_imaxtoa((size_t)va_arg(*ap, size_t)));
	else if (fdatas->length & LENGTH_J)
		return (ft_imaxtoa((intmax_t)va_arg(*ap, intmax_t)));
	else if (fdatas->length & LENGTH_LL)
		return (ft_imaxtoa((long long int)va_arg(*ap, long long int)));
	else if (fdatas->length & LENGTH_L)
		return (ft_imaxtoa((long int)va_arg(*ap, long int)));
	else if (fdatas->length & LENGTH_H)
		return (ft_itoa((short int)va_arg(*ap, int)));
	else if (fdatas->length & LENGTH_HH)
		return (ft_itoa((signed char)va_arg(*ap, int)));
	return (NULL);
}

void			print_formated_digit(va_list *ap, t_fdata *fdatas)
{
	char	*str;
	int		len;

	str = str_from_arg(ap, fdatas);
	if (str[0] == '0' && fdatas->precision == 0)
		str[0] = '\0';
	if (str[0] == '-')
	{
		if (fdatas->precision >= 0)
			fdatas->precision++;
		fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	}
	if (fdatas->flag & (FLAG_MORE | FLAG_SPACE))
		fdatas->width--;
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
