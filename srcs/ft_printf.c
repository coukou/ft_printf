/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:54:24 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 19:41:27 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <stdlib.h>
# include "ft_printf.h"

static void		ft_pf_init(t_pf_state *state, t_pf_buffer *pbuff, const char **fmt, va_list *args)
{
	pbuff->writed = 0;
	state->flags = 0;
	state->precision = -1;
	state->width = - 1;
	state->length = 0;
	state->args = args;
	state->pbuff = pbuff;
	state->fmt = fmt;
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
	if (ft_isdigit(**state->fmt))
		state->precision = ft_pf_atoi(state->fmt);
	else if (**state->fmt == '*')
	{
		state->precision = va_arg(*state->args, int);
		(*state->fmt)++;
	}
	else
		return (0);
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
	if (!(FT_MASK_EQ(state->flags, M_FLAG_MINUS)))
		ft_pf_write_padding(state, state->width - len, pchar);
	ft_pf_buffer_write_n(state->pbuff, data, len);
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS))
		ft_pf_write_padding(state, state->width - len, " ");
}

static void		ft_pf_format_s(t_pf_state *state)
{
	char *tmp;
	size_t len;

	tmp = va_arg(*state->args, char*);
	if (tmp == 0)
		tmp = "(null)";
	len = ft_strlen(tmp);
	if (state->precision > -1 && state->precision < (int)len)
		len = state->precision;
	ft_pf_write_s(state, tmp, len);
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
	else if (state->specifier == 'o')
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

static void		ft_pf_format_di(t_pf_state *state)
{
	char data[64];
	char *sign;
	size_t dlen;
	int precision;
	char *pchar;

	ft_pf_get_di(state, data);
	sign = ft_pf_extract_sign(state, data);
	dlen = ft_strlen(data);
	precision = ((state->precision - (int)dlen) > 0) ? state->precision - dlen : 0;
	pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) && state->precision < 0) ? "0" : " ";
	if (*sign)
	{
		if (!(FT_MASK_EQ(state->flags, M_FLAG_MINUS)) && *pchar != '0')
			ft_pf_write_padding(state, state->width - (dlen + ft_strlen(sign) + precision), pchar);
		ft_pf_buffer_write_n(state->pbuff, sign, 1);
	}
	else if (!(FT_MASK_EQ(state->flags, M_FLAG_MINUS)))
		ft_pf_write_padding(state, state->width - (dlen + ft_strlen(sign) + precision), pchar);
	ft_pf_write_padding(state, precision, "0");
	ft_pf_buffer_write_n(state->pbuff, data, dlen);
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS))
		ft_pf_write_padding(state, state->width - (dlen + ft_strlen(sign) + precision), " ");

}

static void		ft_pf_format_uox(t_pf_state *state)
{
	char tmp[64];

	ft_pf_get_uox(state, tmp);
	ft_pf_buffer_write(state->pbuff, tmp);
}

static int		ft_pf_format_dispatch(int c, t_pf_state *state)
{
	if (c == 's')
		ft_pf_format_s(state);
	else if (c == 'd' || c == 'i')
		ft_pf_format_di(state);
	else if (c == 'u' || c == 'o' || c == 'x' || c == 'X')
		ft_pf_format_uox(state);
	else
		return (0);
	return (1);
}

static void		ft_pf_format(t_pf_state *state)
{
	int rsum;

	rsum = 1;
	while (rsum)
	{
		rsum = 0;
		rsum += ft_pf_get_flags(state);
		rsum += ft_pf_get_width(state);
		rsum += ft_pf_get_precision(state);
		rsum += ft_pf_get_length(state);
	}
	state->specifier = **state->fmt;
	if (!ft_pf_format_dispatch(ft_tolower(**state->fmt), state))
		ft_pf_buffer_write_n(state->pbuff, (char*)*state->fmt, 1);
}

static void		ft_pf_format_color(t_pf_state *state)
{
	printf("format color: %s\n", *state->fmt);
}

int				ft_printf(const char *fmt, ...)
{
	va_list 				args;
	static t_pf_state		*state;
	static t_pf_buffer		*pbuff;

	if (state == NULL && !(state = (t_pf_state*)ft_memalloc(sizeof(*state))))
		return (-1);
	if (pbuff == NULL && !(pbuff = (t_pf_buffer*)ft_memalloc(sizeof(*pbuff))))
		return (-1);
	va_start(args, fmt);
	ft_pf_init(state, pbuff, &fmt, &args);
	while (*fmt)
	{
		if (*fmt == '%' && *(fmt++))
			ft_pf_format(state);
		else if (*fmt == '{' && *(fmt++))
			ft_pf_format_color(state);
		else
			ft_pf_buffer_write_n(pbuff, (char*)fmt, 1);
		fmt++;
	}
	va_end(args);
	ft_pf_buffer_flush(pbuff);
	return (pbuff->writed);
}
