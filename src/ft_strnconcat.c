/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnconcat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:40:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 08:56:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

char	*ft_strnconcat(char *dst, char const *src, int n)
{
	char	*buf;

	buf = dst;
	dst = ft_strnjoin(dst, src, n);
	ft_strdel(&buf);
	return (dst);
}
