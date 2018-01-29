/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:46:39 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/29 14:03:36 by spopieul         ###   ########.fr       */
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
	size_t				width;
	int					length;
	va_list				*args;
	t_pf_buffer			*pbuff;
}				t_pf_state;

char	*ft_litoa(long long n);
char	*ft_get_di(t_pf_state *state);
char	*ft_get_uoxX(t_pf_state *state);
char	*ft_get_s(t_pf_state *state);
char	*ft_get_c(t_pf_state *state);

void	ft_pf_buffer_write(t_pf_buffer *buffer, unsigned char *data, size_t size);
void	ft_pf_buffer_flush(t_pf_buffer *buffer);
int		ft_printf(const char *fmt, ...);

#endif
