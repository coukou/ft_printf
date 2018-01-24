/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:32:08 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/24 17:50:27 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "ft_specifiers.h"

int		is_format_trigger_char(int c)
{
	return (c == '%');
}

int		ft_get_flag(int c)
{
	if (c == '-')
		return (FLAG_MINUS);
	if (c == '+')
		return (FLAG_PLUS);
	if (c == '#')
		return (FLAG_HASH);
	if (c == ' ')
		return (FLAG_SPACE);
	if (c == '0')
		return (FLAG_ZERO);
	return (0);
}

int		ft_get_length(int c)
{
	if (c == 'h')
		return (LENGTH_H);
	if (c == 'l')
		return (LENGTH_L);
	if (c == 'j')
		return (LENGTH_J);
	if (c == 'z')
		return (LENGTH_Z);
	if (c == 'L')
		return (LENGTH_L_);
	return (0);
}

int		ft_is_printf_length_flag(int c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 't' || c == 'L');
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
		else if (length == LENGTH_H)
			state->length ^= LENGTH_HH;
		else if (length == LENGTH_L)
			state->length ^= LENGTH_LL;
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

void	ft_printf_get_width(const char **fmt, t_pf_state *state, va_list *args)
{
	state->width = ft_printf_get_number(fmt, args);
}

void	ft_printf_get_precision(const char **fmt, t_pf_state *state, va_list *args)
{
	if (**fmt != '.')
		return;
	(*fmt)++;
	state->precision = ft_printf_get_number(fmt, args);
}

void	ft_format(const char **fmt, va_list *args, t_printf_buffer *pbuff)
{
	(void)pbuff;
	const char *fmt_ptr;
	t_pf_state state;
	int i;

	fmt_ptr = *fmt;
	ft_bzero(&state, sizeof(state));
	if (*fmt_ptr == '%')
	{
		fmt_ptr++;
		i = -1;
		ft_printf_get_flags(&fmt_ptr, &state);
		ft_printf_get_width(&fmt_ptr, &state, args);
		ft_printf_get_precision(&fmt_ptr, &state, args);
		ft_printf_get_length(&fmt_ptr, &state);
	}
	*fmt = fmt_ptr;
}

int		ft_printf(const char *fmt, ...)
{
	t_printf_buffer pbuff;
	va_list args;

	ft_bzero(&pbuff, sizeof(pbuff));
	va_start(args, fmt);
	while (*fmt)
	{
		if (is_format_trigger_char(*fmt))
			ft_format(&fmt, &args, &pbuff);
		else
			ft_printf_buffer_write(&pbuff, (unsigned char*)fmt, 1);
		fmt++;
	}
	ft_printf_buffer_flush(&pbuff);
	va_end(args);
	return (pbuff.writed);
}
