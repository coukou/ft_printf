/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:01:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/28 17:27:42 by spopieul         ###   ########.fr       */
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

static char*	get_base(int c)
{
	if (c == 'o' || c == 'O')
		return ("01234567");
	else if (c == 'x')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	else
		return ("0123456789");
}

static char *extract_sign(t_pf_state *state, char **data)
{
	(void)state;
	char *tmp;

	if (**data == '-')
	{
		tmp = ft_strdup(*data + 1);
		ft_strdel(data);
		*data = tmp;
		return (ft_strdup("-"));
	}
	if ((state->flags & M_FLAG_PLUS) == M_FLAG_PLUS && state->specifier != 'u')
		return (ft_strdup("+"));
	if ((state->flags & M_FLAG_SPACE) == M_FLAG_SPACE && state->specifier != 'u')
		return (ft_strdup(" "));
	return (ft_strnew(0));
}

static char	*generate_width_padding(t_pf_state *state, int data_len, int force_zero)
{
	int i;
	int width;
	char *padding;
	char pad_char;

	i = -1;
	width = state->width - data_len;
	if (width < 0)
		width = 0;
	padding = ft_strnew(width);
	if (force_zero || ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO && state->precision == -1 &&
		(state->flags & M_FLAG_MINUS) != M_FLAG_MINUS && state->specifier != 's' &&
		state->specifier != 'c'))
		pad_char = '0';
	else
		pad_char = ' ';
	while (++i < width)
		padding[i] = pad_char;
	return (padding);
}

static char	*generate_precision_padding(t_pf_state *state, int data_len)
{
	int i;
	int width;
	char *padding;

	i = -1;
	width = state->precision - data_len;
	if (width < 0)
		width = 0;
	padding = ft_strnew(width);
	while (++i < width)
		padding[i] = '0';
	return (padding);
}

static char	*generate_base_padding(t_pf_state *state, char *data)
{
	if (*data == '0' || *data == 0)
		return (ft_strnew(0));
	if ((state->flags & M_FLAG_HASH) != M_FLAG_HASH)
		return (ft_strnew(0));
	if (state->specifier == 'o' || state->specifier == 'O')
		return (ft_strdup("0"));
	if (state->specifier == 'x')
		return (ft_strdup("0x"));
	if (state->specifier == 'X')
		return (ft_strdup("0X"));
	return (ft_strnew(0));
}

char	*ft_format_diuoxX(t_pf_state *state, char *data)
{
	char *base_padding;
	char *width_padding;
	char *precision_padding;
	char *sign;

	sign = extract_sign(state, &data);
	if (*data == '0' && state->precision == 0)
	{
		if (!((state->flags & M_FLAG_HASH) == M_FLAG_HASH && state->specifier == 'o'))
		{
			ft_strdel(&data);
			data = ft_strnew(0);
		}
	}
	base_padding = generate_base_padding(state, data);
	precision_padding = generate_precision_padding(state, ft_strlen(data));
	data = ft_strjoin_free(precision_padding, data);
	width_padding = generate_width_padding(state, ft_strlen(data) + ft_strlen(sign) + ft_strlen(base_padding), 0);
	if (*width_padding == '0')
	{
		data = ft_strjoin_free(width_padding, data);
		data = ft_strjoin(base_padding, data);
		data = ft_strjoin_free(sign, data);
	}
	else
	{
		data = ft_strjoin_free(base_padding, data);
		data = ft_strjoin_free(sign, data);
		if ((state->flags & M_FLAG_MINUS) == M_FLAG_MINUS)
			data = ft_strjoin_free(data, width_padding);
		else
			data = ft_strjoin_free(width_padding, data);
	}
	return (data);
}

char	*ft_get_s(t_pf_state *state)
{
	char *data;
	char *data_tmp;
	char *width_padding;

	data_tmp = va_arg(*state->args, char*);
	if (data_tmp == 0)
		data_tmp = (state->precision >= 6 || state->precision == -1) ? "(null)" : "";
	if (state->precision < 0)
		data = ft_strdup(data_tmp);
	else
		data = ft_strndup(data_tmp, state->precision);
	width_padding = generate_width_padding(state, ft_strlen(data), 0);
	if ((state->flags & M_FLAG_MINUS) == M_FLAG_MINUS)
		data = ft_strjoin(data, width_padding);
	else
		data = ft_strjoin(width_padding, data);
	return (data);
}

char	*ft_get_c(t_pf_state *state)
{
	char *data;
	char *padding;

	data = ft_strnew(1);
	data[0] = (char)(va_arg(*state->args, int));
	padding = generate_width_padding(state, 1, 0);
	if (data[0] == 0)
	{
		if ((state->flags & M_FLAG_MINUS) == M_FLAG_MINUS)
		{
			ft_pf_buffer_write(state->pbuff, (unsigned char*)"\0", 1);
			ft_pf_buffer_write(state->pbuff, (unsigned char*)padding, ft_strlen(padding));
		}
		else
		{
			ft_pf_buffer_write(state->pbuff, (unsigned char*)padding, ft_strlen(padding));
			ft_pf_buffer_write(state->pbuff, (unsigned char*)"\0", 1);
		}
	}
	else
	{
		if ((state->flags & M_FLAG_MINUS) == M_FLAG_MINUS)
			data = ft_strjoin_free(data, padding);
		else
			data = ft_strjoin_free(padding, data);
	}
	return (data);
}

char	*ft_get_percent(t_pf_state *state)
{
	char *data;
	char *padding;
	int force_zero;

	data = ft_strdup("%");
	force_zero = (state->flags & M_FLAG_ZERO) == M_FLAG_ZERO ? 1 : 0;
	padding = generate_width_padding(state, 1, force_zero);
	if ((state->flags & M_FLAG_MINUS) == M_FLAG_MINUS)
		data = ft_strjoin_free(data, padding);
	else
		data = ft_strjoin_free(padding, data);
	return (data);
}


char	*ft_get_di(t_pf_state *state)
{
	char *data;

	if ((state->length & M_LENGTH_LL) == M_LENGTH_LL)
		data = ft_litoa((long long)va_arg(*state->args, long long));
	else if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		data = ft_litoa((long)va_arg(*state->args, long));
	else if ((state->length & M_LENGTH_HH) == M_LENGTH_HH)
		data = ft_litoa((char)va_arg(*state->args, int));
	else if ((state->length & M_LENGTH_H) == M_LENGTH_H)
		data = ft_litoa((short)va_arg(*state->args, int));
	else if ((state->length & M_LENGTH_J) == M_LENGTH_J)
		data = ft_litoa(va_arg(*state->args, intmax_t));
	else if ((state->length & M_LENGTH_Z) == M_LENGTH_Z)
		data = ft_litoa(va_arg(*state->args, size_t));
	else if ((state->length & M_LENGTH_T) == M_LENGTH_T)
		data = ft_litoa(va_arg(*state->args, long));
	else
		data = ft_litoa(va_arg(*state->args, int));
	return (ft_format_diuoxX(state, data));
}

char	*ft_get_uoxX(t_pf_state *state)
{
	char *data;
	char *base;

	base = get_base(state->specifier);
	if ((state->length & M_LENGTH_LL) == M_LENGTH_LL)
		data = ft_ulitoa((unsigned long long)va_arg(*state->args, unsigned long long), base);
	else if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		data = ft_ulitoa((unsigned long)va_arg(*state->args, unsigned long), base);
	else if ((state->length & M_LENGTH_HH) == M_LENGTH_HH)
		data = ft_ulitoa((unsigned char)va_arg(*state->args, unsigned int), base);
	else if ((state->length & M_LENGTH_H) == M_LENGTH_H)
		data = ft_ulitoa((unsigned short)va_arg(*state->args, unsigned int), base);
	else if ((state->length & M_LENGTH_J) == M_LENGTH_J)
		data = ft_ulitoa(va_arg(*state->args, uintmax_t), base);
	else if ((state->length & M_LENGTH_Z) == M_LENGTH_Z)
		data = ft_ulitoa(va_arg(*state->args, size_t), base);
	else if ((state->length & M_LENGTH_T) == M_LENGTH_T)
		data = ft_ulitoa(va_arg(*state->args, long), base);
	else
		data = ft_ulitoa(va_arg(*state->args, unsigned int), base);
	return (ft_format_diuoxX(state, data));
}
