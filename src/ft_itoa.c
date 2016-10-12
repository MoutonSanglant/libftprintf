/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:38:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:49:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

char			*ft_itoa(int n)
{
	char			*str;
	size_t			sign;
	size_t			l;
	int				n_copy;

	sign = (n < 0);
	l = sign + 1;
	n_copy = n;
	while (n_copy /= 10)
		l++;
	if (!(str = ft_strnew(l)))
		return (NULL);
	str[l] = '\0';
	if (sign != 0)
		str[0] = '-';
	while (l-- > sign)
	{
		str[l] = (sign > 0) ? HEX_TABLE(-(n % 10)) : HEX_TABLE(n % 10);
		n /= 10;
	}
	return (str);
}
