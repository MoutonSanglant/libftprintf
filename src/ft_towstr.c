/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_towstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:45:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/14 16:28:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/*
**	Unicode characters will be 4-bytes long max
**	but UTF-8 can go up to 6-bytes long characters
**	=========================
**	wchar length:
**	0x80-0xc0		==> 2-bytes
**	0xc1-0x7ff		==> 3-bytes
**	0x800-0xffff	==> 4-bytes
**	0x10000-
**	=========================
**	forbidden characters:
**	0xc0, 0xc1, 0xfe, 0xff
**	=========================
**	|raw_byte|
**	|utf_byte|
**	 h+3	  h+2	   h+1		h
**	|00000000|00000000|00000000|0xxxxxxx|
**	|0xxxxxxx|
**	 h+3	  h+2	   h+1		h
**	|00000000|00000000|00000yyy|yyxxxxxx|
**	|110yyyyy|10xxxxxx|
**	 h+3	  h+2	   h+1		h
**	|00000000|00000000|zzzzyyyy|yyxxxxxx|
**	|1110zzzz|10yyyyyy|10xxxxxx|
**	 h+3	  h+2	   h+1		h
**	|00000000|000wwwzz|zzzzyyyy|yyxxxxxx|
**	|11110www|10zzzzzz|10yyyyyy|10xxxxxx|
**	=====================================
**	More than 4-bytes characters
**	 h+3	  h+2	   h+1		h
**	|000000vv|wwwwwwzz|zzzzyyyy|yyxxxxxx|
**	|111110vv|10wwwwww|10zzzzzz|10yyyyyy|10xxxxxx|
**	 h+3	  h+2	   h+1		h
**	|0uvvvvvv|wwwwwwzz|zzzzyyyy|yyxxxxxx|
**	|1111110u|10vvvvvv|10wwwwww|10zzzzzz|10yyyyyy|10xxxxxx|
*/

/*
**	mask12 = 0b00000000000000000000100000000000; <=> (1 << 11)
**	mask17 = 0b00000000000000010000000000000000; <=> (1 << 16)
*/

//static void		convert(unsigned char *h, char **str, int len)
static void		convert(unsigned char *h, char *str, int len)
{
	int		i;

	i = 0;
	if (len <= 2)
		str[i++] =
			((((*h & 0b11000000) >> 6)
				| ((*(h + 1) << 2)
						& 0b00011111)) | 0b11000000);
	else
	{
		if (len <= 3)
			str[i++] = (((*(h + 1) & 0b11110000) >> 4) | 0b11100000);
		else
		{
			if (len <= 4)
				str[i++] = (((*(h + 2) & 0b00011100) >> 2) | 0b11110000);
			else
			{
				if (len <= 5)
					str[i++] = (((*(h + 3) & 0b00000011)) | 0b11111000);
				else
				{
					str[i++] = (((*(h + 3) & 0b01000000)) | 0b11111100);
					str[i++] = (((*(h + 3) & 0b00111111)) | 0b10000000);
				}
				str[i++] = (((*(h + 2) & 0b11111100) >> 2) | 0b10000000);
			}
			str[i++] = ((((*(h + 1) & 0b11110000) >> 4) | ((*(h + 2) << 4)
							& 0b00111111)) | 0b10000000);
		}
		str[i++] = ((((*h & 0b11000000) >> 6) | ((*(h + 1) << 2)
							& 0b00111111)) | 0b10000000);
	}
	str[i++] = ((*h & 0b00111111) | 0b10000000);
}


static int			wstrlen(wchar_t *wstr)
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

#include <stdio.h>

int			ft_towstr(wchar_t *unicode_point, char **str)
{
	//char	*str;
	wchar_t	c;
	int		length;
	int		wchar_size;
	char	*str_ptr;
	char	*end_ptr;

	length = wstrlen(unicode_point);
	*str = (char *)malloc(length + 1);
	str_ptr = *str;
	end_ptr = &(*str)[length];

	printf("[dump] widestring length: %i\n", length);
	fflush(stdout);

	while (str_ptr < end_ptr)
	{
		c = *unicode_point;
		unicode_point++;
		if (c <= MASK7)
		{
			*str_ptr = c;
			str_ptr++;
			continue ;
		}
		if (c <= MASK11)
			wchar_size = 2;
		else if (c <= MASK16)
			wchar_size = 3;
		else if (c <= MASK21)
			wchar_size = 4;
		else if (c <= MASK26)
			wchar_size = 5;
		else
			wchar_size = 6;

		printf("[dump] writting unicode point at address: %p\n", str_ptr);
		fflush(stdout);

		convert((unsigned char *)&c, str_ptr, wchar_size);
		str_ptr += wchar_size;
	}
	(*str)[length] = '\0';
	return (length);
}
