/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/13 21:50:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdio.h>

static void	cpy_to_buffer(void *dst, void const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
}

void	write_to_buffer(const char *format, int count, t_fdata *fdatas)
{
	const char	*spec_char_ptr;
	int idx;

	idx = fdatas->bcount;
	spec_char_ptr = ft_strchr(format, '%');


	printf("[dump] expanding: %i\n", fdatas->expand);
	fflush(stdout);
	//printf("[dump] count: %i bytes\n", count);
	//fflush(stdout);

	if (!fdatas->expand && !spec_char_ptr)
	{
		// reached the end of formating
		//write(1, "=== end reached\n", 16);
		//write_to_buffer(format, (int)ft_formatlen(format), fdatas);
		fdatas->bcount += ft_strlen(format);
		printf("[dump] format: %s\n", format);
		fflush(stdout);

		fdatas->out = (char *)malloc(fdatas->bcount + 1);
		fdatas->out[fdatas->bcount] = '\0'; 
		printf(">>>>>> malloc of size %i <<<<<<<<<\n", fdatas->bcount);
		fflush(stdout);
		//return ;
	}
	else
	{
		//count = spec_char_ptr - format;
		count = spec_char_ptr - fdatas->format;
		fdatas->idx += count;
		fdatas->bcount += count;
		//printf("[dump] bcount: %i\n", fdatas->bcount);
		//fflush(stdout);


		printf("[dump] idx: %i\n", fdatas->idx);
		fflush(stdout);
		printf("[dump] format: %s\n", fdatas->format);
		fflush(stdout);
		//parse(&format[fdatas->bcount], fdatas);
		parse(&fdatas->format[fdatas->idx], fdatas);
	}

	//idx -= count;
	//idx = fdatas->bcount - count;
	//ft_formatncpy(&fdatas->out[idx], format, fdatas->bcount);
	//ft_memcpy(&fdatas->out[idx], format, fdatas->bcount);
	cpy_to_buffer(&fdatas->out[idx], format, count);

	printf("[dump] write %i bytes at idx %i\nfrom: %s\nto  : %s\n", count, idx, format, &fdatas->out[idx]);
	fflush(stdout);
}
