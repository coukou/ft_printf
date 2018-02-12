/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:46:39 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/12 18:21:37 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

# define PRINTF_BUFF_SIZE 64

# define M_FLAG_MINUS	0x01
# define M_FLAG_PLUS	0x02
# define M_FLAG_SPACE	0x04
# define M_FLAG_HASH	0x08
# define M_FLAG_ZERO	0x10

# define M_LENGTH_H		0x01
# define M_LENGTH_HH	0x02
# define M_LENGTH_L		0x04
# define M_LENGTH_LL	0x08
# define M_LENGTH_J		0x10
# define M_LENGTH_Z		0x20
# define M_LENGTH_T		0x40
# define M_LENGTH_L_	0x80

# define M_ALIGN_RIGHT	0
# define M_ALIGN_LEFT	1

# define BASE_UPPERCASE "0123456789ABCDEF"
# define BASE_LOWERCASE "0123456789abcdef"

# define FT_MASK_EQ(value, mask) ((value & mask) == mask)

typedef struct	s_pf_data
{
	char value[65];
	size_t len;
	char *sign;
	char *bpad;
	size_t width;
	size_t precision;
	char *pchar;
}				t_pf_data;

typedef struct	s_pf_buffer
{
	unsigned char	data[PRINTF_BUFF_SIZE + 1];
	size_t			content_size;
	size_t			writed;
}				t_pf_buffer;

typedef struct	s_pf_state
{
	int					specifier;
	int					flags;
	int					precision;
	int					width;
	int					length;
	va_list				*args;
	t_pf_buffer			*pbuff;
	const char			**fmt;
}				t_pf_state;

int			ft_printf(const char *fmt, ...);

void    ft_pf_buffer_flush(t_pf_buffer *buffer);
void    ft_pf_buffer_write_n(t_pf_buffer *buffer, char *data, size_t size);
void    ft_pf_buffer_write(t_pf_buffer *buffer, char *data);

#endif
