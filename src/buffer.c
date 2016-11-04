/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/04 04:32:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"
#include <stdio.h>


static char	*ft_strchr(char const *s, int c)
{
	if ((char)c == '\0')
		return (&((char *)s)[ft_strlen(s)]);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

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

static size_t	memset_buffer_segment(t_fdata *fdatas, int c, size_t offset, size_t len)
{
	size_t	i;
	char	*b;

	len = (offset + len < fdatas->write_size) ? len : fdatas->write_size - offset;
	b = &fdatas->out[offset];
	i = 0;
	while (i < len)
		b[i++] = (unsigned char)c;
	return (i);
}

/*
** Happens on malformated widechar
*/
void	write_error(t_fdata *fdatas)
{
	fdatas->flag |= FLAG_WRITE_ERROR;
	write_to_buffer("", fdatas);
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
	char	*sign; // prefix

	sign = "+";
	sign_position = 0;
	start_offset = 0;
	flags = fdatas->flag;

	int precision = fdatas->precision;
	int to_write = (precision < printed_char) ? printed_char : precision;
	int width = fdatas->width;

	if (flags & FLAG_SPACE)
		sign = " ";
	if (flags & FLAG_NEGATIVE)
		sign = "-";

	if (flags & FLAG_NUMBERSIGN)
	{
		flags |= FLAG_PREFIXED;
		if (*fdatas->stop == 'o' || *fdatas->stop == 'O')
		{
			if (printed_char < precision)
				flags &= ~FLAG_PREFIXED;
			sign = "0";
		}
		else if (*fdatas->stop == 'X')
			sign = "0X";
		else
			sign = "0x";
	}

	if (width <= to_write)
	{
		width = to_write;
		if (sign[1])
			width += 2;
		else if (flags & (FLAG_MORE | FLAG_SPACE | FLAG_NEGATIVE | FLAG_PREFIXED))
			width++;
	}

	start_offset = fdatas->bcount;
	fdatas->bcount += width;
	fdatas->idx = fdatas->stop - fdatas->format + 1;
	parse(&fdatas->format[fdatas->idx], fdatas);

	// ** Expanding **

	// write offset
	write_offset = start_offset;

	// DEBUG, if you see a '!' something is broken
	memset_buffer_segment(fdatas, '!', write_offset, width);

	if (flags & FLAG_LESS)
	{
		if (sign[1])
			write_offset += 2;
		else if (flags & (FLAG_MORE | FLAG_SPACE | FLAG_NEGATIVE | FLAG_PREFIXED))
			write_offset++;
		sign_position = write_offset;
		write_offset += memset_buffer_segment(fdatas, '0', write_offset, to_write - printed_char);
	}
	else if (flags & FLAG_ZERO)
	{
		// ON FLAGZERO WE PRINT ONLY precision characters
		if (precision >= 0)
		{
			write_offset += memset_buffer_segment(fdatas, ' ', start_offset, width - to_write);
			sign_position = write_offset;
			// zerofill
			write_offset += memset_buffer_segment(fdatas, '0', write_offset, to_write - printed_char);
		}
		else
		{
			// !! FULL WIDTH !!
			memset_buffer_segment(fdatas, ' ', start_offset, width);
			// zerofill
			sign_position = write_offset + 1;
			if (sign[1])
				sign_position += 1;
			write_offset += memset_buffer_segment(fdatas, '0', write_offset, width - printed_char);
		}
	}
	else
	{
		write_offset += memset_buffer_segment(fdatas, ' ', start_offset, width - to_write);
		sign_position = write_offset;
		// zerofill
		write_offset += memset_buffer_segment(fdatas, '0', write_offset, to_write - printed_char);
	}

	cpy_fn = (cpy_fn) ? cpy_fn : &cpy_to_buffer;
	printed_char = (write_offset + (size_t)printed_char < fdatas->write_size) ? printed_char : (int)fdatas->write_size - write_offset;
	cpy_fn(&fdatas->out[write_offset], src, printed_char);
	if (flags & (FLAG_NEGATIVE | FLAG_MORE | FLAG_SPACE | FLAG_PREFIXED) || sign[1])
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
		memset_buffer_segment(fdatas, ' ', write_offset, width - to_write);
	}
}

void	write_to_buffer(const void *src, t_fdata *fdatas)
{
	const char	*specifier_addr;
	int			idx;
	int			wcount;

	idx = fdatas->bcount;
	specifier_addr = ft_strchr((char *)src, '%');

	//if (!specifier_addr && !fdatas->out)
	if (!specifier_addr)
	{
		wcount = ft_strlen(src);
		if ((size_t)wcount < fdatas->write_size)
			fdatas->bcount += wcount;
		else
			fdatas->bcount += fdatas->write_size - fdatas->bcount;
		if (!fdatas->out)
			fdatas->out = (char *)malloc(fdatas->bcount + 1);
		fdatas->out[fdatas->bcount] = '\0';
	}
	else
	{
	//printf("spec add: %p, spec: %c\n", specifier_addr, *specifier_addr);
		wcount = specifier_addr - (char *)src;
		fdatas->idx += wcount;
		fdatas->bcount += wcount;
		//printf("idx: %i, bcount: %i, wcount: %i, w_size: %i\n", fdatas->idx, fdatas->bcount, wcount, (int)fdatas->write_size);
		if ((size_t)fdatas->idx < fdatas->write_size)
			parse(&fdatas->format[fdatas->idx], fdatas);
	}
	//	printf("--- idx: %i, bcount: %i, wcount: %i, w_size: %i\n", fdatas->idx, fdatas->bcount, wcount, (int)fdatas->write_size);
	if ((size_t)idx < fdatas->write_size)
	{
		wcount = (idx + (size_t)wcount < fdatas->write_size) ? wcount : (int)fdatas->write_size - idx;
		cpy_to_buffer(&fdatas->out[idx], src, wcount);
	}
}
