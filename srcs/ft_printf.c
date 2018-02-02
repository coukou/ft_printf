/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:32:08 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 18:43:31 by spopieul         ###   ########.fr       */
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
	else if (s == 'd' || s == 'i')
		return (ft_pf_get_di(state));
	else if (s == 'D')
	{
		if ((state->length & M_LENGTH_LL) != M_LENGTH_LL)
			state->length |= M_LENGTH_LL;
		return (ft_pf_get_di(state));
	}
	else if (s == 'u' || s == 'o' || s == 'x' || s == 'X')
		return (ft_pf_get_uoxX(state));
	else if (s == 'U' || s == 'O')
	{
		if ((state->length & M_LENGTH_LL) != M_LENGTH_LL)
			state->length |= M_LENGTH_LL;
		return (ft_pf_get_uoxX(state));
	}
	else if (s == '%')
		return (ft_pf_get_percent(state));
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
	t_pf_data *data;
	t_pf_state state;

	fmt_ptr = *fmt;
	init_state(&state, args, pbuff);
	if (*fmt_ptr == '%')
	{
		fmt_ptr++;
		ft_pf_parse_flags(&fmt_ptr, &state);
		ft_pf_parse_width(&fmt_ptr, &state);
		ft_pf_parse_precision(&fmt_ptr, &state);
		ft_pf_parse_length(&fmt_ptr, &state);
		state.specifier = *fmt_ptr;
		data = ft_pf_get_data(&state);
		if (data)
			write_data(&state, data, pbuff);
		else
			ft_pf_buffer_write_n(pbuff, (unsigned char*)fmt_ptr, 1);
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
		else
			ft_pf_buffer_write_n(&pbuff, (unsigned char*)fmt, 1);
		fmt++;
	}
	ft_pf_buffer_flush(&pbuff);
	va_end(args);
	return (pbuff.writed);
}
