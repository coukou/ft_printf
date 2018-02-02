/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:50:34 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 16:07:01 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_parse_flags(const char **fmt, t_pf_state *state)
{
	int flag;

	while ((flag = ft_pf_get_flag(**fmt)) > 0)
	{
		if ((state->flags & flag) == 0)
			state->flags ^= flag;
		(*fmt)++;
	}
}

void	ft_pf_parse_length(const char **fmt, t_pf_state *state)
{
	int length;

	while ((length = ft_pf_get_length(**fmt)) > 0)
	{
		if ((state->length & length) == 0)
			state->length |= length;
		else if (length == M_LENGTH_H)
			state->length |= M_LENGTH_HH;
		else if (length == M_LENGTH_L)
			state->length |= M_LENGTH_LL;
		(*fmt)++;
	}
}

int		ft_pf_parse_number(const char **fmt, va_list *args)
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

void	ft_pf_parse_width(const char **fmt, t_pf_state *state)
{
	state->width = ft_pf_parse_number(fmt, state->args);
}

void	ft_pf_parse_precision(const char **fmt, t_pf_state *state)
{
	if (**fmt != '.')
		return;
	(*fmt)++;
	state->precision = ft_pf_parse_number(fmt, state->args);
}
