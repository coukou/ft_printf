/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:50:34 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/07 16:31:45 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_parse_flags(const char **fmt, t_pf_state *state)
{
	int flag;

	if ((flag = ft_pf_get_flag(**fmt)) > 0)
	{
		if ((state->flags & flag) == 0)
			state->flags ^= flag;
	}
}

void	ft_pf_parse_length(const char **fmt, t_pf_state *state)
{
	int length;

	if ((length = ft_pf_get_length(**fmt)) > 0)
	{
		if ((state->length & length) == 0)
			state->length |= length;
		else if (length == M_LENGTH_H)
			state->length |= M_LENGTH_HH;
		else if (length == M_LENGTH_L)
			state->length |= M_LENGTH_LL;
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
		if (**fmt == '-' || **fmt == '+')
			(*fmt)++;
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
	return (num);
}

void	ft_pf_parse_width(const char **fmt, t_pf_state *state)
{
	state->width = ft_pf_parse_number(fmt, state->args);
	if (state->width < 0)
	{
		state->width = -state->width;
		state->flags |= M_FLAG_MINUS;
	}
}

void	ft_pf_parse_precision(const char **fmt, t_pf_state *state)
{
	if (**fmt != '.')
		return;
	(*fmt)++;
	state->precision = ft_pf_parse_number(fmt, state->args);
}

void	ft_pf_parse(const char **fmt, t_pf_state *state)
{
	(void)state;
	while (ft_pf_get_flag(**fmt) != 0 || ft_pf_get_length(**fmt) != 0 ||
			ft_isdigit(**fmt) || **fmt == '.' || **fmt == '+' ||
			**fmt == '-' || **fmt == '*')
	{
		ft_pf_parse_flags(fmt, state);
		ft_pf_parse_length(fmt, state);
		if (**fmt == '.')
		{
			(*fmt)++;
			state->precision = ft_pf_parse_number(fmt, state->args);
		}
		else if ((ft_isdigit(**fmt) || **fmt == '-' || **fmt == '*'))
			ft_pf_parse_width(fmt, state);
		else
			(*fmt)++;
	}
}
