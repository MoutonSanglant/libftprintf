/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 18:46:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:48:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef FORBIDDEN

int			ft_vfprintf(FILE *stream, const char *restrict format, va_list *ap)
{
	return (ft_putstr_fd(ft_vdprintf(fileno(stream), format, ap), fd));
}

#else

int			ft_vfprintf(FILE *stream, const char *restrict format, va_list *ap)
{
	(void)stream;
	(void)format;
	(void)ap;
	return (-1);
}

#endif

int			ft_fprintf(FILE *stream, const char *restrict format, ...)
{
	va_list		ap;
	int			count;

	va_start(ap, format);
	count = ft_vfprintf(stream, format, &ap);
	va_end(ap);
	return (count);
}
