/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 18:46:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 07:49:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

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
