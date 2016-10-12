/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 09:00:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void		print(t_fdata *fdatas, char *str)
{
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

static int		justify_long_string(wchar_t *wstr, t_fdata *fdatas, int dry)
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
		if (w_bytes > fdatas->precision)
			return (w_bytes - n);
		else if (!dry)
		{
			str = ft_towstr(&wstr[r_bytes], &len);
			fdatas->out = ft_strconcat(fdatas->out, str);
			ft_strdel(&str);
		}
	}
	return (w_bytes);
}

static void		print_formated_long_string(t_fdata *fdatas, wchar_t *wstr)
{
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

void			print_formated_string(va_list *ap, t_fdata *fdatas, char *s)
{
	wchar_t		*wstr;
	char		*str;

	str = NULL;
	wstr = NULL;
	if (s != NULL)
		str = s;
	else if (fdatas->length == LENGTH_L)
		wstr = (wchar_t *)va_arg(*ap, wchar_t *);
	else
		str = va_arg(*ap, char *);
	if (!str && !wstr)
	{
		fdatas->precision = (fdatas->precision < 0) ? 7 : fdatas->precision;
		if (fdatas->precision < 6)
			str = ft_strdup(" ");
		else
			str = ft_strdup("(null)");
		print(fdatas, str);
		ft_strdel(&str);
	}
	else if (str)
		print(fdatas, str);
	else
		print_formated_long_string(fdatas, wstr);
}
