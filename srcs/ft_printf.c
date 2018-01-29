/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:32:08 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/28 17:32:09 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		ft_get_flag(int c)
{
	if (c == '-')
		return (M_FLAG_MINUS);
	if (c == '+')
		return (M_FLAG_PLUS);
	if (c == '#')
		return (M_FLAG_HASH);
	if (c == ' ')
		return (M_FLAG_SPACE);
	if (c == '0')
		return (M_FLAG_ZERO);
	return (0);
}

int		ft_get_length(int c)
{
	if (c == 'h')
		return (M_LENGTH_H);
	if (c == 'l')
		return (M_LENGTH_L);
	if (c == 'j')
		return (M_LENGTH_J);
	if (c == 'z')
		return (M_LENGTH_Z);
	if (c == 't')
		return (M_LENGTH_T);
	if (c == 'L')
		return (M_LENGTH_L_);
	return (0);
}

void	ft_printf_get_flags(const char **fmt, t_pf_state *state)
{
	int flag;

	while ((flag = ft_get_flag(**fmt)) > 0)
	{
		if ((state->flags & flag) == 0)
			state->flags ^= flag;
		(*fmt)++;
	}
}

void	ft_printf_get_length(const char **fmt, t_pf_state *state)
{
	int length;

	while ((length = ft_get_length(**fmt)) > 0)
	{
		if ((state->length & length) == 0)
			state->length ^= length;
		else if (length == M_LENGTH_H)
			state->length ^= M_LENGTH_HH;
		else if (length == M_LENGTH_L)
			state->length ^= M_LENGTH_LL;
		(*fmt)++;
	}
}

int		ft_printf_get_number(const char **fmt, va_list *args)
{
	int num;

	num = 0;
	if (**fmt == '*')
	{
		num = va_arg(*args, int);
		(*fmt)++;
	}
	else if (ft_isdigit(**fmt) || **fmt == '+' || **fmt == '-')
	{
		num = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
	return (num);
}

void	ft_printf_get_width(const char **fmt, t_pf_state *state)
{
	state->width = ft_printf_get_number(fmt, state->args);
}

void	ft_printf_get_precision(const char **fmt, t_pf_state *state)
{
	if (**fmt != '.')
		return;
	(*fmt)++;
	state->precision = ft_printf_get_number(fmt, state->args);
}

static char		*get_data(t_pf_state *state)
{
	int s;

	s = state->specifier;
	if (s == 'D' || s == 'd' || s == 'i')
		return (ft_get_di(state));
	if (s == 'u' || s == 'U' || s == 'o' || s == 'O' || s == 'x' || s == 'X')
		return (ft_get_uoxX(state));
	if (s == 's')
		return (ft_get_s(state));
	if (s == 'c')
		return (ft_get_c(state));
	if (s == '%')
		return (ft_strdup("%"));
	return (NULL);
}

static void		init_state(t_pf_state *state, va_list *args, t_pf_buffer *pbuff)
{
	state->args = args;
	state->pbuff = pbuff;
	state->flags = 0;
	state->precision = -1;
	state->length = 0;
	state->width = 0;
	state->specifier = 0;
}

void	ft_format(const char **fmt, va_list *args, t_pf_buffer *pbuff)
{
	const char *fmt_ptr;
	char *data;
	t_pf_state state;

	fmt_ptr = *fmt;
	init_state(&state, args, pbuff);
	if (*fmt_ptr == '%')
	{
		fmt_ptr++;
		ft_printf_get_flags(&fmt_ptr, &state);
		ft_printf_get_width(&fmt_ptr, &state);
		ft_printf_get_precision(&fmt_ptr, &state);
		ft_printf_get_length(&fmt_ptr, &state);
		state.specifier = *fmt_ptr;
		if ((data = get_data(&state)))
		{
			ft_pf_buffer_write(pbuff, (unsigned char*)data, ft_strlen(data));
			ft_strdel(&data);
		}
		else
		{
			data = ft_strdupc(*fmt, *(fmt_ptr + 1));
			ft_pf_buffer_write(pbuff, (unsigned char*)data, ft_strlen(data));
			ft_strdel(&data);
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
			ft_format(&fmt, &args, &pbuff);
		else
			ft_pf_buffer_write(&pbuff, (unsigned char*)fmt, 1);
		fmt++;
	}
	ft_pf_buffer_flush(&pbuff);
	va_end(args);
	return (pbuff.writed);
}
