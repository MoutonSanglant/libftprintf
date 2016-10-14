/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 21:04:20 by tdefresn         ###   ########.fr       */
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

void	write_format(const void *src, int wcount, t_fdata *fdatas, void (*fn)(void *dst, const void *, size_t n))
{
	int idx;
	int str_len;

	idx = fdatas->bcount;
	str_len = wcount;

	if (!fdatas->stop)
	{
		write(1, "!! error !!", 12);
	}
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

	if (!fn)
		fn = &cpy_to_buffer;

	fn(&fdatas->out[idx], src, wcount);
}

void	write_to_buffer(const void *src, int wcount, t_fdata *fdatas)
{
	const char	*spec_char_ptr;
	int idx;

	idx = fdatas->bcount;
	spec_char_ptr = ft_strchr((char *)src, '%');

	if (!spec_char_ptr)
	{
		wcount = ft_strlen(src);
		fdatas->bcount += wcount;
		fdatas->out = (char *)malloc(fdatas->bcount + 1);
		fdatas->out[fdatas->bcount] = '\0';
	}
	else
	{
		wcount = spec_char_ptr - (char *)src;
		fdatas->idx += wcount;
		fdatas->bcount += wcount;
		/*
		printf("[dump]\nstr: '%s'\nidx: %i\n", fdatas->format, fdatas->idx);
		fflush(stdout);
		printf("[dump]\nnew char: '%s'\n", &fdatas->format[fdatas->idx]);
		fflush(stdout);
		*/

		parse(&fdatas->format[fdatas->idx], fdatas);
	}
	cpy_to_buffer(&fdatas->out[idx], src, wcount);
}
