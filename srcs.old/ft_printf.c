/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:32:08 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/08 20:56:51 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static t_pf_data	*ft_pf_get_data(t_pf_state *state)
{
	int s;

	s = state->specifier;
	if (s == 's')
		return (ft_pf_get_s(state));
	else if (s == 'c')
		return (ft_pf_get_c(state));
	else if (s == 'C')
		return (ft_pf_get_C(state));
	else if (s == 'S')
		return (ft_pf_get_S(state));
	else if (s == 'p')
		return (ft_pf_get_p(state));
	else if (s == 'd' || s == 'i')
		return (ft_pf_get_di(state));
	else if (s == 'D')
	{
		state->length |= M_LENGTH_L;
		return (ft_pf_get_di(state));
	}
	else if (s == 'u' || s == 'o' || s == 'x' || s == 'X')
		return (ft_pf_get_uoxX(state));
	else if (s == 'U' || s == 'O')
	{
		state->length |= M_LENGTH_L;
		return (ft_pf_get_uoxX(state));
	}
	else if (s == '%')
		return (ft_pf_get_percent(state));
	return (ft_pf_get_unknown(state));
}

static void		init_state(t_pf_state *state, va_list *args, t_pf_buffer *pbuff)
{
	state->args = args;
	state->pbuff = pbuff;
	state->flags = 0;
	state->precision = -1;
	state->length = 0;
	state->width = 0;
	state->base = 0;
	state->b_uppercase = 0;
	state->specifier = 0;
}

static char		*ft_strtolower(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}

static char		*ft_get_color_code(char *color, int bg)
{
	int ret;

	ret = (bg) ? 40 : 30;
	if (ft_strcmp(color, "black") == 0)
		ret += 0;
	else if (ft_strcmp(color, "red") == 0)
		ret += 1;
	else if (ft_strcmp(color, "green") == 0)
		ret += 2;
	else if (ft_strcmp(color, "yellow") == 0)
		ret += 3;
	else if (ft_strcmp(color, "blue") == 0)
		ret += 4;
	else if (ft_strcmp(color, "magenta") == 0)
		ret += 5;
	else if (ft_strcmp(color, "cyan") == 0)
		ret += 6;
	else if (ft_strcmp(color, "white") == 0)
		ret += 7;
	else if (ft_strcmp(color, "reset") == 0)
		ret = 0;
	else
		return (NULL);
	return (ft_itoa(ret));
}

static int		ft_atoi_base_get_value(const char *base, int c)
{
	int i;

	i = -1;
	while (base[++i])
		if (base[i] == c)
			return (i);
	return (0);
}

static int		ft_atoi_base(const char *str, const char *base)
{
	int res;
	int i;
	int base_len;

	i = -1;
	res = 0;
	base_len = ft_strlen(base);
	while (str[++i])
	{
		res *= base_len;
		res += ft_atoi_base_get_value(base, str[i]);
	}
	return (res);
}

static void		ft_hex_to_rgb(char *hex, int *r, int *g, int *b)
{
	int value;

	value = ft_atoi_base(hex, "0123456789abcdef");
	if (ft_strlen(hex) == 3)
	{
		*r = (((value >> 8) & 0xF) << 4) | 0xf;
		*g = (((value >> 4) & 0xF) << 4) | 0xF;
		*b = ((value & 0xF) << 4) | 0xf;
	}
	else
	{
		*r = ((value >> 16) & 0xFF);
		*g = ((value >> 8) & 0xFF);
		*b = (value & 0xFF);
	}
}

static char		*ft_get_hex_color_code(char *color, int bg)
{
	char *ret;
	int r;
	int g;
	int b;

	ret = (bg) ? ft_strdup("48;2") : ft_strdup("38;2");
	ft_hex_to_rgb(color, &r, &g, &b);
	ret = ft_strjoin_free(ret, ft_strjoin_free(ft_strdup(";"), ft_itoa(r)));
	ret = ft_strjoin_free(ret, ft_strjoin_free(ft_strdup(";"), ft_itoa(g)));
	ret = ft_strjoin_free(ret, ft_strjoin_free(ft_strdup(";"), ft_itoa(b)));
	return (ret);
}

static void		ft_write_color(t_pf_buffer *pbuff, char *color)
{
	int bg;
	int light;
	char *color_code;

	if ((bg = (ft_tolower(*color) == 'b' && ft_tolower(*(color + 1)) == 'g')))
		color += 2;
	if ((light = (ft_tolower(*color) == 'l')))
		color += 1;
	ft_pf_buffer_write(pbuff, (unsigned char*)"\033[");
	color_code = *color == '#' ? ft_get_hex_color_code(color + 1, bg) : ft_get_color_code(color, bg);
	ft_pf_buffer_write(pbuff, (unsigned char*)color_code);
	if (light)
		ft_pf_buffer_write(pbuff, (unsigned char*)";1");
	ft_pf_buffer_write(pbuff, (unsigned char*)"m");
	ft_strdel(&color_code);
}

static void		ft_format_color(const char **fmt, t_pf_buffer *pbuff)
{
	char *color;
	char *end;

	if (!(end = ft_strchr(*fmt, '}')))
		return;
	(*fmt)++;
	color = ft_strndup(*fmt, end - *fmt);
	*fmt += end - *fmt;
	color = ft_strtolower(color);
	ft_write_color(pbuff, color);
	ft_strdel(&color);
}

void	ft_format(const char **fmt, va_list *args, t_pf_buffer *pbuff)
{
	const char *fmt_ptr;
	t_pf_data *data;
	t_pf_state state;

	fmt_ptr = *fmt;
	init_state(&state, args, pbuff);
	if (*fmt_ptr == '%')
	{
		fmt_ptr++;
		ft_pf_parse(&fmt_ptr, &state);
		if (*fmt_ptr)
		{
			state.specifier = *fmt_ptr;
			data = ft_pf_get_data(&state);
			write_data(&state, data, pbuff);
		}
	}
	*fmt = fmt_ptr;
}

int		ft_printf(const char *fmt, ...)
{
	t_pf_buffer pbuff;
	va_list args;

	pbuff.content_size = 0;
	pbuff.writed = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			if (*(fmt + 1) != 0)
				ft_format(&fmt, &args, &pbuff);
		}
		else if (*fmt == '{')
		{
			if (*(fmt + 1) != 0)
				ft_format_color(&fmt, &pbuff);
		}
		else
			ft_pf_buffer_write_n(&pbuff, (unsigned char*)fmt, 1);
		if (*fmt)
			fmt++;
	}
	ft_pf_buffer_flush(&pbuff);
	va_end(args);
	return (pbuff.writed);
}
