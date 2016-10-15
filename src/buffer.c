/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/15 23:07:34 by tdefresn         ###   ########.fr       */
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
// printed_char: nombre de caracteres a imprimer (sans les modificateurs)
void	write_format(const void *src, int printed_char, t_fdata *fdatas, void (*cpy_fn)(void *dst, const void *, size_t n))
{
	t_fflag	flags;
	int		start_offset;
	int		write_offset;
	int		sign_position;
	char	*sign;

	sign = "+";
	sign_position = 0;
	start_offset = 0;
	flags = fdatas->flag;

	if (!fdatas->stop)
		write(1, "!! error !!", 12);

	//int precision = (fdatas->precision < printed_char) ? printed_char : fdatas->precision;
	int precision = fdatas->precision;
	int to_write = (precision < printed_char) ? printed_char : precision;
	int width = fdatas->width;

	if (flags & FLAG_SPACE)
		sign = " ";
	if (flags & FLAG_NEGATIVE)
		sign = "-";

	if (flags & FLAG_NUMBERSIGN)
	{
		if (*fdatas->stop == 'X')
			sign = "0X";
		else
			sign = "0x";
	}

	if (width <= to_write)
	{
		width = to_write;
		if (sign[1])
			width += 2;
		else if (flags & (FLAG_MORE | FLAG_SPACE | FLAG_NEGATIVE))
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

	// DEBUG, if you see a '!' something is broken
	memset_buffer_segment(&fdatas->out[write_offset], '!', width);

	if (flags & FLAG_LESS)
	{
		if (sign[1])
			write_offset += 2;
		else if (flags & (FLAG_MORE | FLAG_SPACE | FLAG_NEGATIVE))
			write_offset++;
		sign_position = write_offset;
		write_offset += memset_buffer_segment(&fdatas->out[write_offset], '0', to_write - printed_char);
	}
	else if (flags & FLAG_ZERO)
	{
		// ON FLAGZERO WE PRINT ONLY precision characters
		if (precision >= 0)
		{
			write_offset += memset_buffer_segment(&fdatas->out[start_offset], ' ', width - to_write);
			sign_position = write_offset;
			// zerofill
			write_offset += memset_buffer_segment(&fdatas->out[write_offset], '0', to_write - printed_char);
		}
		else
		{
			// !! FULL WIDTH !!
			memset_buffer_segment(&fdatas->out[start_offset], ' ', width);
			// zerofil
			sign_position = write_offset + 1;
			if (sign[1])
				sign_position += 1;
			write_offset += memset_buffer_segment(&fdatas->out[write_offset], '0', width - printed_char);
		}
	}
	else
	{
		write_offset += memset_buffer_segment(&fdatas->out[start_offset], ' ', width - to_write);
		sign_position = write_offset;
		// zerofil
		write_offset += memset_buffer_segment(&fdatas->out[write_offset], '0', to_write - printed_char);
	}

	cpy_fn = (cpy_fn) ? cpy_fn : &cpy_to_buffer;
	cpy_fn(&fdatas->out[write_offset], src, printed_char);
	if (flags & (FLAG_NEGATIVE | FLAG_MORE | FLAG_SPACE) || sign[1])
	{
		int sign_len;
		int i;

		i = 0;
		sign_len = ft_strlen(sign);
		sign_position -= sign_len;
		while (i < sign_len)
		{
			fdatas->out[sign_position + i] = sign[i];
			i++;
		}
		to_write += sign_len;
	}

	if (fdatas->flag & FLAG_LESS)
	{
		write_offset += printed_char;
		//memset_buffer_segment(&fdatas->out[write_offset], ' ', width - to_write);
		memset_buffer_segment(&fdatas->out[write_offset], ' ', width - to_write);
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
