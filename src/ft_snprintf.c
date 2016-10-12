/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 18:46:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 07:50:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int		ft_vsnprintf(char *restrict str, size_t size, const char *restrict format, va_list *ap)
{
	int		out;

	(void)str;
	(void)size;
	(void)format;
	(void)ap;
	out = 0;
	return (out);
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
