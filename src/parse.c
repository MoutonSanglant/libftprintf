/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 17:58:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 19:32:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static char			*ft_strpbrk(const char *s1, const char *s2)
{
	int		i;

	while (*s1)
	{
		i = 0;
		while (s2[i])
		{
			if (*s1 == s2[i])
				return ((char *)s1);
			i++;
		}
		s1++;
	}
	return (NULL);
}

static int			get_precision_width_length(const char **f, t_fdata *d)
{
	if (**f == '.' && (*f += 1))
	{
		d->precision = ft_atoi(*f);
		while (isdigit(**f))
			*f += 1;
		*f -= 1;
	}
	else if (isdigit(**f))
	{
		d->width = ft_atoi(*f);
		while (isdigit(**f))
			*f += 1;
		*f -= 1;
	}
	else if (**f == 'h')
		d->length |= (*(*f + 1) == 'h' && (*f += 1)) ? LENGTH_HH : LENGTH_H;
	else if (**f == 'l')
		d->length |= (*(*f + 1) == 'l' && (*f += 1)) ? LENGTH_LL : LENGTH_L;
	else if (**f == 'j')
		d->length |= LENGTH_J;
	else if (**f == 'z')
		d->length |= LENGTH_Z;
	else
		return (0);
	return (1);
}

static const char	*get_format_datas(const char *format,
									const char *specifier, t_fdata *d)
{
	d->flag = FLAG_NONE;
	d->width = 0;
	d->precision = -1;
	d->length = LENGTH_NONE;
	while (format < specifier)
	{
		if (*format == '-')
			d->flag |= FLAG_LESS;
		else if (*format == '+')
			d->flag |= FLAG_MORE;
		else if (*format == ' ')
			d->flag |= FLAG_SPACE;
		else if (*format == '#')
			d->flag |= FLAG_NUMBERSIGN;
		else if (*format == '0')
			d->flag |= FLAG_ZERO;
		else if (!get_precision_width_length(&format, d))
		{
			specifier = format;
			break ;
		}
		format++;
	}
	d->fill_char = (d->flag & FLAG_ZERO && !(d->flag & FLAG_LESS)) ? "0" : " ";
	return (specifier);
}

static int			is_long(const char *spec)
{
	return (*spec == 'S' || *spec == 'D'
			|| *spec == 'O' || *spec == 'U' || *spec == 'C');
}

static int			check_common_spec(t_fdata *fdatas, const char *spec)
{
	if (*spec == 's' || *spec == 'S')
		print_formated_string(fdatas, NULL);
	else if (*spec == 'p')
		print_formated_pointer(fdatas);
	else if (*spec == 'i' || *spec == 'd' || *spec == 'D')
		print_formated_digit(fdatas);
	else if (*spec == 'o' || *spec == 'O')
		print_formated_octal(fdatas);
	else if (*spec == 'u' || *spec == 'U')
		print_formated_unsigned(fdatas);
	else if (*spec == 'x' || *spec == 'X')
		print_formated_hex(fdatas);
	else
		return (0);
	return (1);
}

static void			expand(const char *format, t_fdata *fdatas)
{
	const char	*spec;

	if (!(spec = ft_strpbrk(format, "sSpdDioOuUxXcC%")))
		spec = get_format_datas(format, format + ft_strlen(format), fdatas);
	else
		spec = get_format_datas(format, spec, fdatas);
	fdatas->stop = spec;
	if (is_long(spec))
		fdatas->length = LENGTH_L;
	if (!check_common_spec(fdatas, spec))
	{
		if (*spec == 'c')
		{
			if (print_formated_char(fdatas) < 0)
				return ;
		}
		else if (*spec == 'C')
		{
			if (print_formated_widechar(fdatas) < 0)
				return ;
		}
		else
			print_formated_space(fdatas);
	}
	return ;
}

void				parse(const char *format, t_fdata *fdatas)
{
	if (*format == '%')
		expand(&format[1], fdatas);
	else
		write_to_buffer(format, fdatas);
}
