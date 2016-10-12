/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:38:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 03:34:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef DEBUG

int		ft_putstr_fd(char const *s, int fd)
{
	if (!s)
	{
		ft_printf("ft_putstr_fd: param error");
		return (-1);
	}
	return (write(fd, s, ft_strlen(s)));
}

#else

int		ft_putstr_fd(char const *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}
#endif
