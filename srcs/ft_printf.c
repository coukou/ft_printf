/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:54:24 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/12 22:51:56 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_printf.h"

static void		ft_pf_init(t_pf_state *state, t_pf_buffer *pbuff, va_list *args)
{
	pbuff->writed = 0;
	pbuff->content_size = 0;

	state->args = args;
	state->pbuff = pbuff;
}

static int		ft_pf_atoi(const char **fmt)
{
	int res;
	int n;

	res = 0;
	n = 1;
	while (ft_isspace(**fmt))
		(*fmt)++;
	if (**fmt == '-')
		n = -1;
	if (**fmt == '-' || **fmt == '+')
		(*fmt)++;
	while (ft_isdigit(**fmt))
	{
		res *= 10;
		res += **fmt - '0';
		(*fmt)++;
	}
	return (res * n);
}

static int		ft_pf_get_width(t_pf_state *state)
{
	if (**state->fmt == '.')
		return (0);
	if (ft_isdigit(**state->fmt))
		state->width = ft_pf_atoi(state->fmt);
	else if (**state->fmt == '*')
	{
		state->width = va_arg(*state->args, int);
		(*state->fmt)++;
	}
	else
		return (0);
	return (1);
}

static int		ft_pf_get_precision(t_pf_state *state)
{
	if (**state->fmt != '.')
		return (0);
	(*state->fmt)++;
	if (**state->fmt == '*')
	{
		state->precision = va_arg(*state->args, int);
		(*state->fmt)++;
	}
	else
		state->precision = ft_pf_atoi(state->fmt);
	return (1);
}

static int		ft_pf_get_length(t_pf_state *state)
{
	if (**state->fmt == 'l' && *((*state->fmt) + 1) != 'l')
		state->length |= M_LENGTH_L;
	else if (**state->fmt == 'l' && (*state->fmt)++)
		state->length |= M_LENGTH_LL;
	else if (**state->fmt == 'h' && *((*state->fmt) + 1) != 'h')
		state->length |= M_LENGTH_H;
	else if (**state->fmt == 'h' && (*state->fmt)++)
		state->length |= M_LENGTH_HH;
	else if (**state->fmt == 'j')
		state->length |= M_LENGTH_J;
	else if (**state->fmt == 'z')
		state->length |= M_LENGTH_Z;
	else if (**state->fmt == 't')
		state->length |= M_LENGTH_T;
	else if (**state->fmt == 'L')
		state->length |= M_LENGTH_L_;
	else
		return (0);
	(*state->fmt)++;
	return (1);
}

static int		ft_pf_get_flags(t_pf_state *state)
{
	int result;

	result = 0;
	while (**state->fmt)
	{
		if (**state->fmt == '+')
			state->flags |= M_FLAG_PLUS;
		else if (**state->fmt == '-')
			state->flags |= M_FLAG_MINUS;
		else if (**state->fmt == ' ')
			state->flags |= M_FLAG_SPACE;
		else if (**state->fmt == '#')
			state->flags |= M_FLAG_HASH;
		else if (**state->fmt == '0')
			state->flags |= M_FLAG_ZERO;
		else
			return (result);
		(*state->fmt)++;
		result = 1;
	}
	return (result);
}

static void		ft_pf_write_padding(t_pf_state *state, int width, char *pchar)
{
	while (width-- > 0)
		ft_pf_buffer_write_n(state->pbuff, pchar, 1);
}

static void		ft_pf_write_s(t_pf_state *state, char *data, size_t len)
{
	char *pchar;

	pchar = FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ";
	if (!FT_MASK_EQ(state->flags, M_FLAG_MINUS))
		ft_pf_write_padding(state, state->width - len, pchar);
	ft_pf_buffer_write_n(state->pbuff, data, len);
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS))
		ft_pf_write_padding(state, state->width - len, " ");
}

static void		ft_pf_write_ws(t_pf_state *state, wchar_t *data, size_t len)
{
	char tmp[5];
	char *pchar;
	int i;
	size_t size;
	size_t wclen;

	i = -1;
	size = ft_wstrlen(data);
	pchar = FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ";
	if (!FT_MASK_EQ(state->flags, M_FLAG_MINUS))
		ft_pf_write_padding(state, state->width - len, pchar);
	while (++i < size)
	{
		wclen = ft_wclen(data[i]);
		ft_wctoa(data[i], tmp);
		ft_pf_buffer_write_n(state->pbuff, tmp, wclen);
	}
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS))
		ft_pf_write_padding(state, state->width - len, " ");
}

static void		ft_pf_get_di(t_pf_state *state, char out[])
{
	if (FT_MASK_EQ(state->length, M_LENGTH_LL))
		ft_lltoa(va_arg(*state->args, long long), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_L))
		ft_lltoa(va_arg(*state->args, long), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_HH))
		ft_lltoa((char)va_arg(*state->args, int), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_H))
		ft_lltoa((short)va_arg(*state->args, int), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_J))
		ft_lltoa(va_arg(*state->args, intmax_t), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_Z))
		ft_lltoa(va_arg(*state->args, size_t), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_T))
		ft_lltoa(va_arg(*state->args, long), 10, out);
	else
		ft_lltoa(va_arg(*state->args, int), 10, out);
}

static int		ft_pf_get_base(t_pf_state *state)
{
	if (state->specifier == 'x' || state->specifier == 'X')
		return (16);
	else if (state->specifier == 'o' || state->specifier == 'O')
		return (8);
	else
		return (10);
}

static void		ft_pf_get_uox(t_pf_state *state, char out[])
{
	int base;

	base = ft_pf_get_base(state);
	if (FT_MASK_EQ(state->length, M_LENGTH_LL))
		ft_ulltoa(va_arg(*state->args, unsigned long long), base, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_L))
		ft_ulltoa(va_arg(*state->args, unsigned long), base, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_HH))
		ft_ulltoa((unsigned char)va_arg(*state->args, unsigned int), base, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_H))
		ft_ulltoa((unsigned short)va_arg(*state->args, unsigned int), base, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_J))
		ft_ulltoa(va_arg(*state->args, uintmax_t), base, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_Z))
		ft_ulltoa(va_arg(*state->args, size_t), base, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_T))
		ft_ulltoa(va_arg(*state->args, long), base, out);
	else
		ft_ulltoa(va_arg(*state->args, unsigned int), base, out);
	if (ft_islower(state->specifier))
		ft_strtolower(out);
}

static char		*ft_pf_extract_sign(t_pf_state *state, char data[])
{
	int i;

	i = -1;
	if (*data == '-')
	{
		while (data[++i])
			data[i] = data[i + 1];
		return ("-");
	}
	else if (FT_MASK_EQ(state->flags, M_FLAG_PLUS))
		return ("+");
	else if (FT_MASK_EQ(state->flags, M_FLAG_SPACE))
		return (" ");
	else
		return ("");
}

static void		ft_pf_write_data(t_pf_state *state, t_pf_data *data)
{
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS) || state->width < -1)
	{
		ft_pf_buffer_write(state->pbuff, data->sign);
		ft_pf_buffer_write(state->pbuff, data->bpad);
		ft_pf_write_padding(state, data->precision, "0");
		ft_pf_buffer_write_n(state->pbuff, data->value, data->len);
		ft_pf_write_padding(state, data->width, " ");
	}
	else
	{
		if (*data->pchar == '0')
		{
			ft_pf_buffer_write(state->pbuff, data->bpad);
			ft_pf_buffer_write(state->pbuff, data->sign);
			ft_pf_write_padding(state, data->width, data->pchar);
		}
		if (*data->pchar != '0')
		{
			ft_pf_write_padding(state, data->width, data->pchar);
			ft_pf_buffer_write(state->pbuff, data->sign);
			ft_pf_buffer_write(state->pbuff, data->bpad);
		}
		ft_pf_write_padding(state, data->precision, "0");
		ft_pf_buffer_write_n(state->pbuff, data->value, data->len);
	}
}

static size_t	ft_pf_get_pad_width(t_pf_state *state, t_pf_data *data)
{
	int width;
	int slen;
	int dlen;
	int blen;

	dlen = (int)data->len + data->precision;
	slen = (int)ft_strlen(data->sign);
	blen = (int)ft_strlen(data->bpad);
	width = (state->width < -1) ? FT_ABS(state->width) : state->width;
	return (FT_MIN(width - dlen - slen - blen, 0));
}

static void		ft_pf_format_di(t_pf_state *state)
{
	t_pf_data data;

	if (state->specifier == 'D')
		state->length |= M_LENGTH_L;
	ft_pf_get_di(state, data.value);
	data.sign = ft_pf_extract_sign(state, data.value);
	data.len = ft_strlen(data.value);
	if (*data.value == '0' && state->precision == 0)
		data.len = 0;
	data.bpad = "";
	data.precision = FT_MIN(state->precision - (int)data.len, 0);
	data.width = ft_pf_get_pad_width(state, &data);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) && state->precision < 0 ? "0" : " ");
	ft_pf_write_data(state, &data);
}

static char		*ft_pf_get_base_padding(t_pf_state *state, t_pf_data *data)
{
	int s;

	if (!FT_MASK_EQ(state->flags, M_FLAG_HASH))
		return ("");
	s = state->specifier;
	if (*data->value == '0' && ft_tolower(s) != 'o')
		return ("");
	if (*data->value == '0' && ft_tolower(s) == 'o' && state->precision == -1)
		return ("");
	if (s == 'x')
		return ("0x");
	else if (s == 'X')
		return ("0X");
	else if (ft_tolower(s) == 'o')
		return ("0");
	else
		return ("");
}

static void		ft_pf_format_uox(t_pf_state *state)
{
	t_pf_data data;

	if (state->specifier == 'U' || state->specifier == 'O')
		state->length |= M_LENGTH_L;
	ft_pf_get_uox(state, data.value);
	data.sign = ft_pf_extract_sign(state, data.value);
	data.sign = "";
	data.len = ft_strlen(data.value);
	if (*data.value == '0' && state->precision == 0)
		data.len = 0;
	data.bpad = ft_pf_get_base_padding(state, &data);
	data.precision = FT_MIN(state->precision - (int)data.len, 0);
	data.width = ft_pf_get_pad_width(state, &data);
	if (ft_tolower(state->specifier) == 'o')
		data.precision -= (int)ft_strlen(data.bpad);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	ft_pf_write_data(state, &data);
}

static void		ft_pf_format_percent(t_pf_state *state)
{
	t_pf_data data;

	data.value[0] = '%';
	data.len = 1;
	data.bpad = "";
	data.precision = 0;
	data.width = FT_MIN(state->width - 1, 0);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	data.sign = "";
	ft_pf_write_data(state, &data);
}

static void		ft_pf_format_wc(t_pf_state *state)
{
	wchar_t tmp;
	t_pf_data data;

	tmp = va_arg(*state->args, wchar_t);
	ft_wctoa(tmp, data.value);
	data.len = ft_wclen(tmp);
	data.bpad = "";
	data.precision = 0;
	data.sign = "";
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	data.width = data.width = ft_pf_get_pad_width(state, &data);
	ft_pf_write_data(state, &data);
}

static void		ft_pf_format_c(t_pf_state *state)
{
	t_pf_data data;

	if (FT_MASK_EQ(state->length, M_LENGTH_L))
	{
		ft_pf_format_wc(state);
		return ;
	}
	data.value[0] = (char)va_arg(*state->args, int);
	data.len = 1;
	data.bpad = "";
	data.precision = 0;
	data.sign = "";
	data.width = ft_pf_get_pad_width(state, &data);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	ft_pf_write_data(state, &data);
}

static void		ft_pf_format_unknown(t_pf_state *state)
{
	t_pf_data data;

	data.value[0] = state->specifier;
	data.len = 1;
	data.bpad = "";
	data.precision = 0;
	data.sign = "";
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	data.width = data.width = ft_pf_get_pad_width(state, &data);
	ft_pf_write_data(state, &data);
}

static void		ft_pf_format_p(t_pf_state *state)
{
	t_pf_data data;

	ft_lltoa(va_arg(*state->args, intptr_t), 16, data.value);
	ft_strtolower(data.value);
	data.len = (state->precision == 0) ? 0 : ft_strlen(data.value);
	data.bpad = "0x";
	data.precision = FT_MIN(state->precision - data.len, 0);
	data.width = FT_MIN(state->width - (data.len + 2), 0);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	data.sign = "";
	ft_pf_write_data(state, &data);
}

static void		ft_pf_format_ws(t_pf_state *state)
{
	// wchar_t *tmp;
	// t_pf_data data;

	// tmp = va_arg(*state->args, wchar_t*);
	// if (tmp == 0)
	// 	tmp = L"(null)";
	// if (state->precision < 0)
	// 	ft_wstrtoa(tmp, data.value);
	// else
	// 	ft_wstrtoa_n(tmp, state->precision, data.value);
	// data.len = ft_strlen(data.value);
	// data.bpad = "";
	// data.precision = 0;
	// data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	// data.sign = "";
	// data.width = FT_MIN(ft_pf_get_pad_width(state, &data), 0);
	// ft_pf_write_data(state, &data);
}

static void		ft_pf_format_s(t_pf_state *state)
{
	char *tmp;
	size_t len;

	if (FT_MASK_EQ(state->length, M_LENGTH_L))
	{
		ft_pf_format_ws(state);
		return ;
	}
	tmp = va_arg(*state->args, char*);
	if (tmp == 0)
		tmp = "(null)";
	len = ft_strlen(tmp);
	if (state->precision > -1 && state->precision < (int)len)
		len = state->precision;
	ft_pf_write_s(state, tmp, len);
}

static void		ft_pf_format_dispatch(int c, t_pf_state *state)
{
	if (state->specifier == 'S')
		ft_pf_format_ws(state);
	else if (state->specifier == 'C')
		ft_pf_format_wc(state);
	else if (c == 's')
		ft_pf_format_s(state);
	else if (c == 'c')
		ft_pf_format_c(state);
	else if (c == 'p')
		ft_pf_format_p(state);
	else if (c == 'd' || c == 'i')
		ft_pf_format_di(state);
	else if (c == 'u' || c == 'o' || c == 'x')
		ft_pf_format_uox(state);
	else if (c == '%')
		ft_pf_format_percent(state);
	else
		ft_pf_format_unknown(state);
	(*state->fmt)++;
}

static void		ft_pf_format(t_pf_state *state)
{
	int rsum;

	rsum = 1;
	state->flags = 0;
	state->precision = -1;
	state->width = -1;
	state->length = 0;
	while (rsum)
	{
		rsum = 0;
		rsum += ft_pf_get_flags(state);
		rsum += ft_pf_get_width(state);
		rsum += ft_pf_get_precision(state);
		rsum += ft_pf_get_length(state);
	}
	state->specifier = **state->fmt;
	ft_pf_format_dispatch(ft_tolower(**state->fmt), state);
}


int				ft_printf(const char *fmt, ...)
{
	va_list 			args;
	static t_pf_state	state;
	static t_pf_buffer	pbuff;

	va_start(args, fmt);
	ft_pf_init(&state, &pbuff, &args);
	state.fmt = &fmt;
	while (*fmt)
	{
		if (*fmt == '%' && *(++fmt))
			ft_pf_format(&state);
		// else if (*fmt == '{' && *(++fmt))
		// 	ft_pf_format_color(&state);
		else if (*fmt)
			ft_pf_buffer_write_n(&pbuff, (char*)fmt++, 1);
	}
	va_end(args);
	ft_pf_buffer_flush(&pbuff);
	return (pbuff.writed);
}
