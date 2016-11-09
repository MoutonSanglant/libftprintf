/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 19:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/09 01:05:39 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

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

static void		buffer_memcpy(void *dst, void const *src, size_t n)
{
	char		*p_dst;
	const char	*p_src;

	p_dst = dst;
	p_src = src;
	while (n--)
		*p_dst++ = *p_src++;
}

static size_t	segment_memset(t_fdata *fdatas, int c, size_t off, size_t len)
{
	size_t	i;
	char	*b;

	len = (off + len < fdatas->write_size) ? len : fdatas->write_size - off;
	b = &fdatas->out[off];
	i = 0;
	while (i < len)
		b[i++] = (unsigned char)c;
	return (i);
}

typedef struct	s_segment
{
	int		width;
	int		start_offset;
	int		write_offset;
	int		sign_position;
	char	sign[3];
}				t_segment;

static void	set_segment_sign(t_segment *segment, t_fdata *fdatas, int str_len)
{
	t_fflag	flags;

	segment->sign[0] = '+';
	segment->sign[1] = '\0';
	flags = fdatas->flag;
	if (flags & FLAG_SPACE)
		segment->sign[0] = ' ';
	if (flags & FLAG_NEGATIVE)
		segment->sign[0] = '-';
	if (flags & FLAG_NUMBERSIGN)
	{
		flags |= FLAG_PREFIXED;
		segment->sign[0] = '0';
		if ((*fdatas->stop == 'o' || *fdatas->stop == 'O'))
		{
			if (str_len < fdatas->precision)
				flags &= ~FLAG_PREFIXED;
		}
		else
		{
			segment->sign[1] = (*fdatas->stop == 'p') ? 'x' : *fdatas->stop;
			segment->sign[2] = '\0';
		}
	}
	fdatas->flag = flags;
}

void	set_segment_width(t_segment *segment, int print_len, t_fflag flags)
{
	if (segment->width <= print_len)
	{
		segment->width = print_len;
		if (segment->sign[1])
			segment->width += 2;
		else if (flags & FLAG_PREFIXED)
			segment->width++;
	}
}

void		write_padding(t_fdata *fdatas, t_segment *segment, int print_len, int str_len)
{
	int			zerofill_len;

	zerofill_len = print_len - str_len;
	if (fdatas->flag & FLAG_LESS)
	{
		if (segment->sign[1])
			segment->write_offset += 2;
		else if (fdatas->flag & FLAG_PREFIXED)
			segment->write_offset++;
		segment->sign_position = segment->write_offset;
	}
	else if (fdatas->flag & FLAG_ZERO && fdatas->precision < 0)
	{
		segment->sign_position = segment->write_offset + 1;
		if (segment->sign[1])
			segment->sign_position += 1;
		zerofill_len = segment->width - str_len;
	}
	else
	{
		segment->write_offset += segment_memset(fdatas, ' ', segment->start_offset, segment->width - print_len);
		segment->sign_position = segment->write_offset;
	}
	segment->write_offset += segment_memset(fdatas, '0', segment->write_offset, zerofill_len);
}



int			write_prefix(t_segment *segment, t_fdata *fdatas)
{
	int sign_len;
	int i;

	i = 0;
	sign_len = (segment->sign[1]) ? 2 : 1;
	segment->sign_position -= sign_len;
	while (i < sign_len)
	{
		fdatas->out[segment->sign_position + i] = segment->sign[i];
		i++;
	}
	return (sign_len);
}

/*
** segment.width: nombre d'octets a imprimer
** precision: nombre minimum de caracteres a afficher
** str_len: taille de la chaine à imprimer (sans modificateurs)
** print_len: taille réelle à imprimer (avec modificateurs)
*/

void	write_format(const void *src, int str_len, t_fdata *fdatas,
							void (*write_fn)(void *dst, const void *, size_t n))
{
	t_segment	segment;
	int			print_len;

	ft_bzero(&segment, sizeof(t_segment));
	segment.width = fdatas->width;
	segment.start_offset = fdatas->bcount;
	set_segment_sign(&segment, fdatas, str_len);
	print_len = (fdatas->precision < str_len) ? str_len : fdatas->precision;
	set_segment_width(&segment, print_len, fdatas->flag);

	// OUTPUT
	fdatas->bcount += segment.width;
	fdatas->idx = fdatas->stop - fdatas->format + 1;
	parse(&fdatas->format[fdatas->idx], fdatas);

	segment.write_offset = segment.start_offset;

	write_padding(fdatas, &segment, print_len, str_len);
	str_len = (segment.write_offset + (size_t)str_len < fdatas->write_size) ? str_len : (int)fdatas->write_size - segment.write_offset;

	write_fn = (write_fn) ? write_fn : &buffer_memcpy;
	write_fn(&fdatas->out[segment.write_offset], src, str_len);
	if (fdatas->flag & FLAG_PREFIXED || segment.sign[1])
		print_len += write_prefix(&segment, fdatas);
	if (fdatas->flag & FLAG_LESS)
		segment_memset(fdatas, ' ', segment.write_offset + str_len, segment.width - print_len);
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
		buffer_memcpy(&fdatas->out[idx], src, wcount);
	}
}
