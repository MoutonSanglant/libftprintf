/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:46:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/16 02:52:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void			print_formated_pointer(t_fdata *fdatas)
{
	if (fdatas->flag & FLAG_ZERO)
		fdatas->flag |= FLAG_LESS;
	fdatas->flag |= FLAG_NUMBERSIGN;
	fdatas->length = LENGTH_LL;
	print_formated_hex(fdatas);
}
