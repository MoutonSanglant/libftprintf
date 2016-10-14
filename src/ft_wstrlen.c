/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 17:20:15 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 17:20:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int			ft_wstrlen(wchar_t *wstr)
{
	wchar_t	unicode_point;
	int		bcount;
	int		i;

	i = 0;
	bcount = 0;
	while ((unicode_point = wstr[i]))
	{
		if (unicode_point <= MASK7)
			bcount += 1;
		else if (unicode_point <= MASK11)
			bcount += 2;
		else if (unicode_point <= MASK16)
			bcount += 3;
		else if (unicode_point <= MASK21)
			bcount += 4;
		else if (unicode_point <= MASK26)
			bcount += 5;
		else
			bcount += 6;
		i++;
	}
	return (bcount);
}
