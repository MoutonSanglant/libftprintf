/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:40:50 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 03:32:27 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef DEBUG

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	size_t	i;
	size_t	max;

	if (!dst || !src)
	{
		ft_printf("ft_strncpy: param error");
		return (NULL);
	}
	max = ft_strlen(src);
	i = 0;
	while (i < n)
	{
		if (i < max)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}

#else

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	size_t	i;
	size_t	max;

	max = ft_strlen(src);
	i = 0;
	while (i < n)
	{
		if (i < max)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}
#endif
