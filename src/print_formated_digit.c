/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_digit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:45:59 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/15 06:55:02 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
static void		print_prefixes(char **str, t_fdata *fdatas)
{
	if ((*str)[0] == '-')
	{
		(*str)++;
		write_format("-", 1, fdatas);
		//fdatas->out = ft_strconcat(fdatas->out, "-");
		fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	}
	else if (fdatas->flag & FLAG_MORE)
		write_format("+", 1, fdatas);
		//fdatas->out = ft_strconcat(fdatas->out, "+");
	else if (fdatas->flag & FLAG_SPACE)
		write_format(" ", 1, fdatas);
		//fdatas->out = ft_strconcat(fdatas->out, " ");
}
*/

/*
static void		justify_left(t_fdata *fdatas, char *str)
{
	
	if (str[0] == '-' || (fdatas->flag & (FLAG_MORE | FLAG_SPACE)))
		print_prefixes(&str, fdatas);
	while (fdatas->precision-- > 0)
		write_format("0", 1, fdatas);
		//fdatas->out = ft_strconcat(fdatas->out, "0");
		//
	write_format(str, ft_strlen(str), fdatas);
	
	//fdatas->out = ft_strconcat(fdatas->out, str);
	while (fdatas->width-- > 0)
		write_format(fdatas->fill_char, 1, fdatas);
		//fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
	
}
*/

/*
static void		justify_right(t_fdata *fdatas, char *str)
{
	if (fdatas->flag & FLAG_ZERO)
	{
		if (str[0] == '-' || (fdatas->flag & (FLAG_MORE | FLAG_SPACE)))
			print_prefixes(&str, fdatas);
		while (fdatas->width-- > 0)
			write_format(fdatas->fill_char, 1, fdatas);
			//fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
	}
	else
	{
		while (fdatas->width-- > 0)
			write_format(fdatas->fill_char, 1, fdatas);
			//fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
		if (str[0] == '-' || (fdatas->flag & (FLAG_MORE | FLAG_SPACE)))
			print_prefixes(&str, fdatas);
	}
	while (fdatas->precision-- > 0)
		write_format("0", 1, fdatas);

		//fdatas->out = ft_strconcat(fdatas->out, "0");

	// whole new logic:
	// send size of STR + padding (clamped with precision)

	//write_format(str, ft_strlen(str), fdatas);
	//fdatas->out = ft_strconcat(fdatas->out, str);
}
*/
/*
static char		*str_from_arg(t_fdata *fdatas)
{
	if (fdatas->length == LENGTH_NONE)
		return (ft_itoa(va_arg(*fdatas->ap, int)));
	else if (fdatas->length & LENGTH_Z)
		return (ft_imaxtoa((size_t)va_arg(*fdatas->ap, size_t)));
	else if (fdatas->length & LENGTH_J)
		return (ft_imaxtoa((intmax_t)va_arg(*fdatas->ap, intmax_t)));
	else if (fdatas->length & LENGTH_LL)
		return (ft_imaxtoa((long long int)va_arg(*fdatas->ap, long long int)));
	else if (fdatas->length & LENGTH_L)
		return (ft_imaxtoa((long int)va_arg(*fdatas->ap, long int)));
	else if (fdatas->length & LENGTH_H)
		return (ft_itoa((short int)va_arg(*fdatas->ap, int)));
	else if (fdatas->length & LENGTH_HH)
		return (ft_itoa((signed char)va_arg(*fdatas->ap, int)));
	return (NULL);
}
*/

static void	conversion(void *dst, const void *src, size_t n)
{
	char		*to;
	char		*str;
	intptr_t	value;
	int			sign;

	value = (intptr_t)*((intptr_t *)src);
	//sign = (value < 0) ? 1 : 0;
	sign = (value < 0) ? 1 : 0;
	str = &((char *)dst)[n - 1];
	to = (char *)dst;
	while (str >= to)
	{
		*str-- = (sign > 0) ? HEX_TABLE(-(value % 10)) : HEX_TABLE(value % 10);
		value /= 10;
	}
	dst = (void *)str;
}

static size_t		nblen(intptr_t value)
{
	size_t		l;

	l = 1;
	while (value /= 10)
		l++;
	return (l);
}

void			print_formated_digit(t_fdata *fdatas)
{
	intmax_t	value;
	size_t		length;

	if ((value = va_int(fdatas)))
	{
		length = nblen(value);
		if (value < 0)
			fdatas->flag |= FLAG_NEGATIVE;
		write_format(&value, length, fdatas, conversion);
	}
	/*
	char	*str;
	int		len;

	str = str_from_arg(fdatas);
	if (str[0] == '0' && fdatas->precision == 0)
		str[0] = '\0';
	if (str[0] == '-')
	{
		//if (fdatas->precision >= 0)
		//	fdatas->precision++;
		fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	}
	//if (fdatas->flag & (FLAG_MORE | FLAG_SPACE))
	//	fdatas->width--;
	//if (fdatas->precision >= 0)
	//	fdatas->fill_char = " ";
	len = ft_strlen(str);
	//fdatas->precision = fdatas->precision - len;
	//fdatas->precision = (fdatas->precision > 0) ? fdatas->precision : 0;
	//fdatas->width = fdatas->width - fdatas->precision - len;
	//if (fdatas->flag & FLAG_LESS)
	//	justify_left(fdatas, str);
	//else
	//	justify_right(fdatas, str);

	// NEW:
	//printf("width: %i\n", fdatas->width);
	//fflush(stdout);
	//int len = ft_strlen(str);
	//fdatas->width = (fdatas->width > len) ? fdatas->width : len;
	//write_format(str, fdatas->width, fdatas);
	write_format(str, len, fdatas, NULL);
	// ===========

	ft_strdel(&str);
	*/
}
