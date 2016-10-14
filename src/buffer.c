/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 15:59:39 by tdefresn         ###   ########.fr       */
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

static void	*memset_buffer_segment(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		((char *)b)[i++] = (unsigned char)c;
	return (b);
}

void	write_to_buffer(const char *src, int wcount, t_fdata *fdatas)
{
	const char	*spec_char_ptr;
	int idx;

	idx = fdatas->bcount;

	spec_char_ptr = ft_strchr(src, '%');

	//printf("[dump] stop: %c (%p)\n", *fdatas->stop, fdatas->stop);
	//printf("[dump] stop: (%p)\n", fdatas->stop);
	//fflush(stdout);

	if (!fdatas->stop && !spec_char_ptr)
	{
		// increment bcount with remaining caracters
		fdatas->bcount += ft_strlen(src);

		//printf("[dump] bcount: %i\n", fdatas->bcount);
		//fflush(stdout);

		fdatas->out = (char *)malloc(fdatas->bcount + 1);
		fdatas->out[fdatas->bcount] = '\0';

		//printf(">>>>>> malloc of size %i <<<<<<<<<\n", fdatas->bcount + 1);
		//fflush(stdout);
	}
	else
	{
		if (fdatas->stop)
		{
			int str_len = ft_strlen(src);
			int precision = (fdatas->precision > str_len) ? fdatas->precision : str_len;
			int width = fdatas->width;

			if (width < precision)
			{
				width = precision;

				if (fdatas->flag & FLAG_LESS && fdatas->flag & (FLAG_MORE | FLAG_SPACE))
					width++;
			}
			else if (!(fdatas->flag & FLAG_LESS) && fdatas->flag & (FLAG_MORE | FLAG_SPACE))
				idx--;


			//printf("[dump]\nstr: %s\nlength: %i\nprecision: %i\nwidth: %i\n", src, str_len, precision, width);

			fdatas->bcount += width;
			fdatas->idx = fdatas->stop - fdatas->format + 1;
			parse(&fdatas->format[fdatas->idx], fdatas);

			// ** Special operations **
			// print default width
			memset_buffer_segment(&fdatas->out[idx], (int)*fdatas->fill_char, width);

			// padding (right/left)
			if (!(fdatas->flag & FLAG_LESS))
				idx += width - precision;

			// print ' ' or '+' sign
			if (fdatas->flag & (FLAG_MORE | FLAG_SPACE))
				fdatas->out[idx++] = (FLAG_MORE) ? '+' : ' ';


			// print default precision
			memset_buffer_segment(&fdatas->out[idx], '0', precision);

			// write offset
			idx += precision - str_len;
		}
		else
		{
			wcount = spec_char_ptr - fdatas->format;

			// increment index & bcount
			fdatas->idx += wcount;
			fdatas->bcount += wcount;

			//printf("[dump]\nstr: %s\n", src);

			/*
			printf("[dump] bcount: %i\n", fdatas->bcount);
			fflush(stdout);
			printf("[dump] idx: %i\n", fdatas->idx);
			fflush(stdout);
			printf("[dump] format: %s\n", fdatas->format);
			fflush(stdout);
			*/

			// Continue parsing at correct idx
			parse(&fdatas->format[fdatas->idx], fdatas);
		}
	}

	//memset_buffer_segment(&fdatas->out[idx], *fdatas->fill_char, count);
	cpy_to_buffer(&fdatas->out[idx], src, wcount);

	//printf("[dump] write %i bytes at idx %i\nfrom: %s\nto  : %s\n", wcount, idx, src, &fdatas->out[idx]);
	//fflush(stdout);
}
