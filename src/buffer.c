/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/15 08:49:46 by tdefresn         ###   ########.fr       */
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

static size_t	memset_buffer_segment(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		((char *)b)[i++] = (unsigned char)c;
	return (i);
}

// width: nombre d'octets a imprimer
// precision: nombre minimum de caracteres a afficher
void	write_format(const void *src, int printed_char, t_fdata *fdatas, void (*cpy_fn)(void *dst, const void *, size_t n))
{
	t_fflag	flags;
	int		start_offset;
	int		write_offset;

	start_offset = 0;
	flags = fdatas->flag;

	if (!fdatas->stop)
	{
		write(1, "!! error !!", 12);
	}
	

	int precision = (fdatas->precision < printed_char) ? printed_char : fdatas->precision;
	//int precision = fdatas->precision;
	int width = fdatas->width;

	if (width <= precision)
	{
		width = precision;
		if (flags & (FLAG_MORE | FLAG_SPACE | FLAG_NEGATIVE))
			width++;
	}

	//printf("\n[dump]\nstr: %s\nwcount: %i\nprecision: %i\nwidth: %i\n", src, wcount, precision, width);


	start_offset = fdatas->bcount;
	fdatas->bcount += width;
	fdatas->idx = fdatas->stop - fdatas->format + 1;
	parse(&fdatas->format[fdatas->idx], fdatas);

	// ** Expanding **

	// write offset
	write_offset = start_offset;

	if (flags & FLAG_LESS)
	{
		if (flags & FLAG_NEGATIVE)
			fdatas->out[write_offset - 1] = '-';
		else if (flags & FLAG_MORE)
			fdatas->out[write_offset - 1] = '+';
		else if (flags & FLAG_SPACE)
			fdatas->out[write_offset - 1] = ' ';

		write_offset += memset_buffer_segment(&fdatas->out[write_offset], '0', precision - printed_char);
	}
	else if (flags & FLAG_ZERO)
	{
		if (precision > printed_char)
		{
			write_offset += memset_buffer_segment(&fdatas->out[start_offset], ' ', width - precision);
			memset_buffer_segment(&fdatas->out[write_offset], '0', precision - printed_char);
			if (flags & FLAG_NEGATIVE)
				fdatas->out[write_offset - 1] = '-';
			else if (flags & FLAG_MORE)
				fdatas->out[write_offset - 1] = '+';
			else if (flags & FLAG_SPACE)
				fdatas->out[write_offset - 1] = ' ';
			write_offset +=  precision - printed_char;
		}
		else
		{
			memset_buffer_segment(&fdatas->out[start_offset], ' ', width);
			memset_buffer_segment(&fdatas->out[write_offset], '0', width - printed_char);
			if (flags & FLAG_NEGATIVE)
				fdatas->out[write_offset] = '-';
			else if (flags & FLAG_MORE)
				fdatas->out[write_offset] = '+';
			else if (flags & FLAG_SPACE)
				fdatas->out[write_offset] = ' ';
			write_offset += width - printed_char;
		}
	}
	else
	{
		write_offset += memset_buffer_segment(&fdatas->out[start_offset], ' ', width - precision);

		if (flags & FLAG_NEGATIVE)
			fdatas->out[write_offset - 1] = '-';
		else if (flags & FLAG_MORE)
			fdatas->out[write_offset - 1] = '+';
		else if (flags & FLAG_SPACE)
			fdatas->out[write_offset - 1] = ' ';

		write_offset += memset_buffer_segment(&fdatas->out[write_offset], '0', precision - printed_char);
	}

	cpy_fn = (cpy_fn) ? cpy_fn : &cpy_to_buffer;
	cpy_fn(&fdatas->out[write_offset], src, printed_char);

	if (fdatas->flag & FLAG_LESS)
	{
		write_offset += printed_char;
		memset_buffer_segment(&fdatas->out[write_offset], ' ', width - precision);
	}
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
