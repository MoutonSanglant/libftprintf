/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/02 00:21:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/16 03:38:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void	*st_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		((char *)b)[i++] = (unsigned char)c;
	return (b);
}

/*
** dynamically allocate memory inside `ret`
** returns string length
*/
int		ft_vasprintf(char **ret, const char *format, va_list *ap)
{
	t_fdata		fdatas;

	st_memset(&fdatas, 0, sizeof(t_fdata));
	fdatas.ap = ap;
	fdatas.format = format;
	parse(format, &fdatas);
	if (!fdatas.out) // Returns -1 if a widechar is > 4 bytes
		return (-1);
	*ret = fdatas.out;
	if (fdatas.flag & FLAG_WRITE_ERROR)
		return (-1);
	return (fdatas.bcount);
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
