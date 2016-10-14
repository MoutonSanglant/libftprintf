/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 22:37:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
static void		print(t_fdata *fdatas, char *str)
{
	return;
	int		len;

	len = ft_strlen(str);
	fdatas->precision = (fdatas->precision >= 0) ? fdatas->precision : len;
	fdatas->precision = (fdatas->precision < len) ? fdatas->precision : len;
	fdatas->width = fdatas->width - fdatas->precision;
	if (fdatas->flag & FLAG_LESS)
		fdatas->out = ft_strnconcat(fdatas->out, str, fdatas->precision);
	while (fdatas->width > 0)
	{
		fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		fdatas->out = ft_strnconcat(fdatas->out, str, fdatas->precision);
}
*/


/*
//static int		justify_long_string(wchar_t *wstr, t_fdata *fdatas, int dry)
static int		justify_long_string(wchar_t *wstr, t_fdata *fdatas)
{
	int		r_bytes;
	int		w_bytes;
	int		n;
	int		len;
	char	*str;

	r_bytes = -1;
	w_bytes = 0;
	while (wstr[++r_bytes])
	{
		n = 6;
		if (wstr[r_bytes] <= MASK7)
			n = 1;
		else if (wstr[r_bytes] <= MASK11)
			n = 2;
		else if (wstr[r_bytes] <= MASK16)
			n = 3;
		else if (wstr[r_bytes] <= MASK21)
			n = 4;
		else if (wstr[r_bytes] <= MASK26)
			n = 5;
		w_bytes += n;
		//if (w_bytes > fdatas->precision)
		//	return (w_bytes - n);
		//else if (!dry)
		//{
			str = ft_towstr(&wstr[r_bytes], &len);
			//fdatas->out = ft_strconcat(fdatas->out, str);
			write_format(str, len, fdatas);
			ft_strdel(&str);
		//}
	}
	return (w_bytes);
}
*/


/*
static void		print_formated_long_string(t_fdata *fdatas, wchar_t *wstr)
{
	return;
	int		w_bytes;

	fdatas->precision = (fdatas->precision >= 0) ? fdatas->precision : INT_MAX;
	w_bytes = justify_long_string(wstr, fdatas, 1);
	if (fdatas->flag & FLAG_LESS)
		justify_long_string(wstr, fdatas, 0);
	fdatas->width = (fdatas->width > 0) ? fdatas->width : 0;
	fdatas->width -= w_bytes;
	while (fdatas->width-- > 0)
		fdatas->out = ft_strnconcat(fdatas->out, fdatas->fill_char, 1);
	if (!(fdatas->flag & FLAG_LESS))
		justify_long_string(wstr, fdatas, 0);
}
*/

/*
static void	print_null(void *dst, const void *src, size_t n)
{
	char	*str;

	str = dst;
	if (fdatas->precision >= 6)
	{
		*str++ = '(';
		*str++ = 'n';
		*str++ = 'u';
		*str++ = 'l';
		*str++ = 'l';
		*str++ = ')';
	}
}*/

static void	print_null(t_fdata *fdatas)
{
	//fdatas->precision = (fdatas->precision < 0) ? 7 : fdatas->precision;
	//write_format("(null)", 6, fdatas, &print_null);
	write_format("(null)", 6, fdatas, NULL);
}

static void	conversion(void *dst, const void *src, size_t n)
{
	ft_wstrcpy((char *)dst, (wchar_t *)src, n);
}

static void	print_wide(t_fdata *fdatas)
{
	wchar_t		*wstr;

	if ((wstr = (wchar_t *)va_arg(*fdatas->ap, wchar_t *)))
		write_format(wstr, ft_wstrlen(wstr), fdatas, &conversion);
	else
		print_null(fdatas);

}

static void	print_ascii(t_fdata *fdatas)
{
	char		*str;

	if ((str = va_arg(*fdatas->ap, char *)))
		write_format(str, ft_strlen(str), fdatas, NULL);
	else
		print_null(fdatas);
}

static void	print_constant(t_fdata *fdatas, char *str)
{
	if (str)
		write_format(str, ft_strlen(str), fdatas, NULL);
	else
		print_null(fdatas);
}
void			print_formated_string(t_fdata *fdatas, char *s)
{

	if (s != NULL)
		print_constant(fdatas, s);
	else if (fdatas->length == LENGTH_L)
		print_wide(fdatas);
	else
		print_ascii(fdatas);
}
