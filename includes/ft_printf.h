/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:46:39 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/07 14:53:16 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "../libs/libft/includes/libft.h"

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

typedef struct	s_pf_data
{
	char *value;
	size_t vlen;
	char *sign;
	char *base_padding;
	int pad_char;
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
	int					base;
	int					b_uppercase;
	va_list				*args;
	t_pf_buffer			*pbuff;
}				t_pf_state;

int		ft_wchar_len(wchar_t wchar);
int		ft_wstr_len(wchar_t *wstr);
char	*ft_wtoa(wchar_t wchar);
char	*ft_wstoa(wchar_t *wstr);
char	*ft_wstoa_n(wchar_t *wstr, size_t n);

t_pf_data	*ft_create_data();
int			ft_pf_get_flag(int c);
int			ft_pf_get_length(int c);
int			ft_pf_get_pad_length(t_pf_state *state, t_pf_data *data);
char		*ft_pf_get_base_padding(t_pf_state *state, char *data);
char    	*extract_sign(t_pf_state *state, char **data);

void		write_data(t_pf_state *state, t_pf_data *data, t_pf_buffer *pbuff);

char		*ft_pf_get_base(t_pf_state *state);

char		*ft_ultoa(unsigned long long n, char *base);
char		*ft_ltoa(long long n);

void		ft_pf_parse(const char **fmt, t_pf_state *state);
void		ft_pf_parse_flags(const char **fmt, t_pf_state *state);
void		ft_pf_parse_width(const char **fmt, t_pf_state *state);
void		ft_pf_parse_precision(const char **fmt, t_pf_state *state);
void		ft_pf_parse_length(const char **fmt, t_pf_state *state);

t_pf_data	*ft_pf_get_s(t_pf_state *state);
t_pf_data	*ft_pf_get_c(t_pf_state *state);
t_pf_data	*ft_pf_get_p(t_pf_state *state);
t_pf_data	*ft_pf_get_C(t_pf_state *state);
t_pf_data	*ft_pf_get_S(t_pf_state *state);
t_pf_data	*ft_pf_get_unknown(t_pf_state *state);
t_pf_data	*ft_pf_get_percent(t_pf_state *state);
t_pf_data	*ft_pf_get_di(t_pf_state *state);
t_pf_data	*ft_pf_get_uoxX(t_pf_state *state);
t_pf_data	*ft_format_diuoxX(t_pf_state *state, char *data_tmp);

void		ft_pf_buffer_write(t_pf_buffer *buffer, unsigned char *data);
void		ft_pf_buffer_write_n(t_pf_buffer *buffer, unsigned char *data, size_t size);
void		ft_pf_buffer_flush(t_pf_buffer *buffer);
int			ft_printf(const char *fmt, ...);

char 	*ppad_data(t_pf_state *state, char *data, char *basep);

#endif
