/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:39:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 08:51:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef DEBUG

void	ft_strdel(char **as)
{
	if (!as)
	{
		ft_putstr_fd("ft_strdel: param error", 2);
		return ;
	}
	if (!*as)
	{
		ft_putstr_fd("ft_strdel: free error", 2);
		return ;
	}
	free(*as);
	*as = NULL;
}

#else

void	ft_strdel(char **as)
{
	free(*as);
	*as = NULL;
}
#endif
