/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:01:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/22 16:24:24 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pad_data(t_pf_state *state, char *buf)
{
	int width;
	char *padding;
	int pad_char;

	width = state->width - ft_strlen(buf);
	if (width <= 0)
		return (buf);
	if ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO &&
		(state->flags & M_FLAG_MINUS) != M_FLAG_MINUS)
		pad_char = '0';
	else
		pad_char = ' ';
	padding = ft_strnew(width);
	ft_memset(padding, pad_char, width);
	if ((state->flags & M_FLAG_MINUS) == M_FLAG_MINUS)
		return (ft_strjoin_free(buf, padding));
	else
		return (ft_strjoin_free(padding, buf));
}

void	ft_s_specifier(int c, t_pf_state *state)
{
	(void)c;
	char *data;

	data = ft_strdup(va_arg(*state->args, char*));
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, (unsigned char*)data, ft_strlen(data));
}

void	ft_d_specifier(int c, t_pf_state *state)
{
	(void)c;
	int n;
	char *data;

	n = va_arg(*state->args, int);
	data = ft_itoa(n);
	data = pad_data(state, data);
	if ((state->flags & M_FLAG_PLUS) == M_FLAG_PLUS && n >= 0)
		ft_printf_buffer_write(state->pbuff, (unsigned char*)"+", 1);
	ft_printf_buffer_write(state->pbuff, (unsigned char*)data, ft_strlen(data));
}

char	*ft_uitoa(unsigned long n, char *base)
{
	int i;
	char *ret;
	size_t base_len;

	base_len = ft_strlen(base);
	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	ret = ft_strnew(64);
	while (n)
	{
		ret[i++] = base[n % base_len];
		n /= base_len;
	}
	return (ft_strrev(ret));
}

void	ft_u_specifier(int c, t_pf_state *state)
{
	(void)c;
	char *data;

	data = ft_uitoa(va_arg(*state->args, unsigned int), "0123456789");
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, (unsigned char*)data, ft_strlen(data));
}

void	ft_oxX_specifier(int c, t_pf_state *state)
{
	char *data;

	if (c == 'x')
		data = ft_uitoa(va_arg(*state->args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		data = ft_uitoa(va_arg(*state->args, unsigned int), "0123456789ABCDEF");
	else
		data = ft_uitoa(va_arg(*state->args, unsigned int), "01234567");
	if ((state->flags & M_FLAG_HASH) == M_FLAG_HASH)
	{
		if (*data != '0')
		{
			if (c == 'o')
				ft_printf_buffer_write(state->pbuff, (unsigned char*)"0", 1);
			if (c == 'x')
				ft_printf_buffer_write(state->pbuff, (unsigned char*)"0x", 2);
			if (c == 'X')
				ft_printf_buffer_write(state->pbuff, (unsigned char*)"0X", 2);
		}
	}
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, (unsigned char*)data, ft_strlen(data));
}


void	ft_percent_specifier(int c, t_pf_state *state)
{
	(void)state;
	(void)c;
	char *data;

	data = ft_strdup("%");
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, (unsigned char*)data, ft_strlen(data));
}
