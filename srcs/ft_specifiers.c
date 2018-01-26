/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:01:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/26 15:43:09 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


char	*ft_ulitoa(unsigned long long n, char *base)
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

char	*ft_litoa(long long n)
{
	char *ret;

	if (n == 0)
		return (ft_strdup("0"));
	ret = ft_ulitoa(((n < 0) ? -n : n), "0123456789");
	if (n < 0)
		return (ft_strjoin_free(ft_strdup("-"), ret));
	return (ret);
}

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

	data = va_arg(*state->args, char*);
	if (data == 0)
		data = ft_strdup("(null)");
	else
		data = ft_strdup(data);
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, data, ft_strlen(data));
}

void	ft_di_specifier(int c, t_pf_state *state)
{
	(void)c;
	char *data;

	if ((state->length & M_LENGTH_HH) == M_LENGTH_HH)
		data = ft_litoa((char)va_arg(*state->args, int));
	else if ((state->length & M_LENGTH_H) == M_LENGTH_H)
		data = ft_litoa((short)va_arg(*state->args, int));
	else if ((state->length & M_LENGTH_LL) == M_LENGTH_LL)
		data = ft_litoa((long long)va_arg(*state->args, long long));
	else if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		data = ft_litoa((long)va_arg(*state->args, long));
	else if ((state->length & M_LENGTH_J) == M_LENGTH_J)
		data = ft_litoa(va_arg(*state->args, intmax_t));
	else if ((state->length & M_LENGTH_Z) == M_LENGTH_Z)
		data = ft_litoa(va_arg(*state->args, size_t));
	else if ((state->length & M_LENGTH_T) == M_LENGTH_T)
		data = ft_litoa(va_arg(*state->args, long));
	else
		data = ft_litoa(va_arg(*state->args, int));
	if ((state->flags & M_FLAG_PLUS) == M_FLAG_PLUS && *data != '-')
		data = ft_strjoin_free(ft_strdup("+"), data);
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, data, ft_strlen(data));
}

char	*get_base(int c)
{
	if (c == 'x')
		return "0123456789abcdef";
	else if (c == 'X')
		return "0123456789ABCDEF";
	else if (c == 'o')
		return "01234567";
	return "0123456789";
}

char	*get_base_padding(int c)
{
	if (c == 'x')
		return "0x";
	else if (c == 'X')
		return "0X";
	else if (c == 'o')
		return "0";
	return "";
}

void	ft_uoxX_specifier(int c, t_pf_state *state)
{
	char *data;
	char *base;
	char *base_padding;

	base = get_base(c);
	base_padding = get_base_padding(c);
	if ((state->length & M_LENGTH_HH) == M_LENGTH_HH)
		data = ft_ulitoa((unsigned char)va_arg(*state->args, unsigned int), base);
	else if ((state->length & M_LENGTH_H) == M_LENGTH_H)
		data = ft_ulitoa((unsigned short)va_arg(*state->args, unsigned int), base);
	else if ((state->length & M_LENGTH_LL) == M_LENGTH_LL)
		data = ft_ulitoa((unsigned long long)va_arg(*state->args, unsigned long long), base);
	else if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		data = ft_ulitoa((unsigned long)va_arg(*state->args, unsigned long), base);
	else if ((state->length & M_LENGTH_J) == M_LENGTH_J)
		data = ft_ulitoa(va_arg(*state->args, uintmax_t), base);
	else if ((state->length & M_LENGTH_Z) == M_LENGTH_Z)
		data = ft_ulitoa(va_arg(*state->args, size_t), base);
	else if ((state->length & M_LENGTH_T) == M_LENGTH_T)
		data = ft_ulitoa(va_arg(*state->args, long), base);
	else
		data = ft_ulitoa(va_arg(*state->args, unsigned int), base);
	if ((state->flags & M_FLAG_HASH) == M_FLAG_HASH && *data != '0')
		data = ft_strjoin_free(ft_strdup(base_padding), data);
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, data, ft_strlen(data));
}

void	ft_p_specifier(int c, t_pf_state *state)
{
	(void)c;
	(void)state;
}


void	ft_percent_specifier(int c, t_pf_state *state)
{
	(void)state;
	(void)c;
	char *data;

	data = ft_strdup("%");
	data = pad_data(state, data);
	ft_printf_buffer_write(state->pbuff, data, ft_strlen(data));
}
