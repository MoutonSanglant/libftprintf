/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/02 00:21:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/13 21:33:00 by tdefresn         ###   ########.fr       */
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
** TODO return(0) is maybe incorrect
*/
int		ft_vasprintf(char **ret, const char *format, va_list *ap)
{
	t_fdata		fdatas;

	st_memset(&fdatas, '\0', sizeof(t_fdata));
	fdatas.ap = ap;
	fdatas.format = format;
	parse(format, &fdatas);
	if (!fdatas.out)
		return (-1);
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
