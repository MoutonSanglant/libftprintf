/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 18:46:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/13 16:15:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
** write characters inside `str`, `str` needs to be big enough
** returns length of formated string (without \0)
** returns -1 on fail
** TODO unimplemented
*/
int		ft_vsprintf(char *restrict str, const char *restrict format, va_list *ap)
{
	int out;

	(void)format;
	(void)ap;
	(void)str;
	out = 0;
	return (out);
}

int		ft_sprintf(char *restrict str, const char *restrict format, ...)
{
	va_list		ap;
	int			out;

	va_start(ap, format);
	out = ft_vsprintf(str, format, &ap);
	va_end(ap);
	return (out);
}
