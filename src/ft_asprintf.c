/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/02 00:21:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 08:59:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
** return(0) is maybe incorrect
*/

//#include <stdio.h>

int		ft_vasprintf(char **ret, const char *format, va_list *ap)
{
	const char	*from_ptr;
	const char	*to_ptr;
	t_fdata		fdatas;

	fdatas.out = ft_strnew(1);
	fdatas.out[0] = '\0';
	fdatas.bcount = 0;
	from_ptr = format;
	while ((to_ptr = ft_strchr(from_ptr, '%')))
	{
		fdatas.out = ft_strnconcat(fdatas.out, from_ptr, (to_ptr - from_ptr));
		to_ptr = get_formated_argument(ap, (to_ptr + 1), &fdatas);
		if (to_ptr == NULL)
		{
			*ret = fdatas.out;
			return (0);
		}
		to_ptr += 1;
		if (fdatas.flag & FLAG_FORMAT_ERROR)
		{
			*ret = fdatas.out;
			return (ft_strlen(*ret));
		}
		from_ptr = to_ptr;
	}
	fdatas.out = ft_strconcat(fdatas.out, from_ptr);
	*ret = fdatas.out;
	return (ft_strlen(*ret));
}

int		ft_asprintf(char **ret, const char *format, ...)
{
	va_list		ap;
	int			out;

	va_start(ap, format);
	out = ft_vasprintf(ret, format, &ap);
	va_end(ap);
	return (out);
}
