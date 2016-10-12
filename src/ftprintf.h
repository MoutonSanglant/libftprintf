/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:35:58 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:35:58 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

# include "libftprintf.h"

# define HEX_TABLE(x) "0123456789abcdef"[x]
# define HEX_CHECK(s) (s == 'x') ? "0x" : "0X"

/*
**	0x0000007f	-> 0b00000000 00000000 00000000 01111111
**	0x000007ff	-> 0b00000000 00000000 00000111 11111111
**	0x0000ffff	-> 0b00000000 00000000 11111111 11111111
**	0x001fffff	-> 0b00000000 00011111 11111111 11111111
**	0x03ffffff	-> 0b00000011 11111111 11111111 11111111
**	0x7fffffff	-> 0b01111111 11111111 11111111 11111111
*/

# define MASK7 0x0000007f
# define MASK11 0x000007ff
# define MASK16 0x0000ffff
# define MASK21 0x001fffff
# define MASK26 0x03ffffff
# define MASK31 0x7fffffff

typedef enum	e_fflag
{
	FLAG_NONE = 0x0,
	FLAG_LESS = 0x1,
	FLAG_MORE = 0x2,
	FLAG_SPACE = 0x4,
	FLAG_NUMBERSIGN = 0x8,
	FLAG_ZERO = 0x10,
	FLAG_FORMAT_ERROR = 0x20
}				t_fflag;

typedef enum	e_flength
{
	LENGTH_NONE = 0x0,
	LENGTH_HH = 0x1,
	LENGTH_H = 0x2,
	LENGTH_L = 0x4,
	LENGTH_LL = 0x8,
	LENGTH_J = 0x10,
	LENGTH_Z = 0x20
}				t_flength;

typedef struct	s_fdata
{
	char		*out;
	const char	*format;
	char		*fill_char;
	t_fflag		flag;
	t_flength	length;
	int			width;
	int			precision;
	int			bcount;
}				t_fdata;


int				print_formated_char(va_list *ap, t_fdata *fdatas);
int				print_formated_widechar(va_list *ap, t_fdata *fdatas);
void			print_formated_string(va_list *ap, t_fdata *fdatas, char *s);
void			print_formated_pointer(va_list *ap, t_fdata *fdatas);
void			print_formated_digit(va_list *ap, t_fdata *fdatas);
void			print_formated_octal(va_list *ap, t_fdata *fdatas);
void			print_formated_hex(va_list *ap, t_fdata *fdatas,
															char specifier);
void			print_formated_unsigned(va_list *ap, t_fdata *fdatas);
void			print_formated_space(const char *format, t_fdata *fdatas);

const char		*get_formated_argument(va_list *ap, const char *format,
															t_fdata *fdatas);
int				ft_putwchar(wchar_t *unicode_point);
char			*ft_towstr(wchar_t *unicode_point, int *len);

char			*ft_imaxtoa(intmax_t n);
int				ft_isprint(int c);
int				ft_islower(int c);
int				ft_isdigit(int c);
int				ft_isspace(int c);
char			*ft_itoa_base(intmax_t value, int base);
char			*ft_itoa(int n);
int				ft_putstr(char const *s);
int				ft_putstr_fd(char const *s, int fd);
char			*ft_strchr(char const *s, int c);
void			ft_strdel(char **as);
char			*ft_strdup(char const *s1);
size_t			ft_strlen(char const *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strnjoin(char const *s1, char const *s2, int n);
char			*ft_strconcat(char *dst, char const *src);
char			*ft_strnconcat(char *dst, char const *src, int n);
char			*ft_strncpy(char *dst, char const *src, size_t n);
char			*ft_strnew(size_t size);
int				ft_toupper(int c);
char			*ft_uitoa(uintmax_t n);
char			*ft_strpbrk(const char *s1, const char *s2);
int				ft_atoi(char const *str);

#endif
