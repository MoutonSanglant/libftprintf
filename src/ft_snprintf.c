/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 18:46:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/03 21:10:13 by tdefresn         ###   ########.fr       */
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
** write `size - 1` characters inside `str`, `str` needs to be big enough
** returns length of formated string (without \0)
** returns -1 on fail
** TODO unimplemented
*/
int		ft_vsnprintf(char *restrict str, size_t size, const char *restrict format, va_list *ap)
{
	t_fdata		fdatas;

	st_memset(&fdatas, 0, sizeof(t_fdata));
	fdatas.ap = ap;
	fdatas.format = format;
	fdatas.out = str;
	fdatas.write_size = size - 1;
	parse(format, &fdatas);
	// won't work, parse should return an error case
	//if (!fdatas.out) // Returns -1 if a widechar is > 4 bytes
	//	return (-1);
	if (fdatas.flag & FLAG_WRITE_ERROR)
		return (-1);
	return (fdatas.bcount);
}

int		ft_snprintf(char *restrict str, size_t size, const char *restrict format, ...)
{
	va_list		ap;
	int			out;

	va_start(ap, format);
	out = ft_vsnprintf(str, size, format, &ap);
	va_end(ap);
	return (out);
}
