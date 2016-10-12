/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:39:38 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 08:57:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

char	*ft_strconcat(char *dst, char const *src)
{
	char	*buf;

	buf = dst;
	dst = ft_strjoin(dst, src);
	ft_strdel(&buf);
	return (dst);
}
