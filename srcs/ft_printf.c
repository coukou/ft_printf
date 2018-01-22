/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:32:08 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/22 17:50:21 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "ft_specifiers.h"

int		is_format_trigger_char(int c)
{
	return (c == '%');
}

int		ft_is_printf_flag(int c)
{
	return (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0');
}

int		ft_is_printf_length_flag(int c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 't' || c == 'L');
}

void	ft_printf_get_flags(const char **fmt, t_pf_state *state)
{
	while (ft_is_printf_flag(**fmt))
	{
		if (ft_strchr(state->flags, **fmt) == NULL)
			state->flags[ft_strlen(state->flags)] = (**fmt);
		(*fmt)++;
	}
}

void	ft_printf_get_length(const char **fmt, t_pf_state *state)
{
	while (ft_is_printf_length_flag(**fmt))
	{
		state->length[ft_strlen(state->length)] = (**fmt);
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


void	ft_format(const char **fmt, va_list *args)
{
	(void)args;
	const char *fmt_ptr;
	t_pf_state state;
	int i;

	fmt_ptr = *fmt;
	ft_bzero(&state, sizeof(t_pf_state));
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
	char *out;
	va_list args;

	out = ft_strnew(0);
	va_start(args, fmt);
	while (*fmt)
	{
		if (is_format_trigger_char(*fmt))
			ft_format(&fmt, &args);
		else
			ft_putchar(*fmt);
		fmt++;
	}
	va_end(args);
	return (0);
}
