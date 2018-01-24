/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:46:39 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/24 16:02:18 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define PRINTF_BUFF_SIZE 64

# define FLAG_MINUS		0x01
# define FLAG_PLUS		0x02
# define FLAG_SPACE		0x04
# define FLAG_HASH		0x08
# define FLAG_ZERO		0x10

# define LENGTH_H		0x01
# define LENGTH_HH		0x02
# define LENGTH_L		0x04
# define LENGTH_LL		0x08
# define LENGTH_J		0x10
# define LENGTH_Z		0x20
# define LENGTH_T		0x40
# define LENGTH_L_		0x80

typedef struct	s_printf_buffer
{
	char data[PRINTF_BUFF_SIZE + 1];
	size_t content_size;
	size_t writed;
}				t_printf_buffer;

typedef struct	s_pf_state
{
	int		flags;
	size_t	precision;
	size_t	width;
	int		length;
}				t_pf_state;

void	ft_printf_buffer_write(t_printf_buffer *buffer, unsigned char *data, size_t size);
void	ft_printf_buffer_flush(t_printf_buffer *buffer);
int		ft_printf(const char *fmt, ...);

#endif
