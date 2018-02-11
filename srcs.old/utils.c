/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:20:15 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/06 23:01:18 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char    *extract_sign(t_pf_state *state, char **data)
{
	(void)state;
	char *tmp;
	int s;

	s = state->specifier;
	if (**data == '-')
	{
		tmp = ft_strdup(*data + 1);
		ft_strdel(data);
		*data = tmp;
		return ("-");
	}
	if (s == 'x' || s == 'o' || s == 'X' || s == 'O')
		return ("");
	if ((state->flags & M_FLAG_PLUS) == M_FLAG_PLUS && state->specifier != 'u')
		return ("+");
	if ((state->flags & M_FLAG_SPACE) == M_FLAG_SPACE && state->specifier != 'u')
		return (" ");
	return ("");
}

char		*ft_pf_get_base(t_pf_state *state)
{
	char *base;
	int s;

	s = state->specifier;
	if (state->base == 0)
	{
		if (s == 'o' || s == 'O')
			state->base = 8;
		else if (s == 'x' || s == 'X' || s == 'p')
			state->base = 16;
		else
			state->base = 10;
		if (s == 'X')
			state->b_uppercase = 1;
	}
	base = (state->b_uppercase == 1) ? BASE_UPPERCASE : BASE_LOWERCASE;
	return (ft_strndup(base, state->base));
}

char		*ft_pf_get_base_padding(t_pf_state *state, char *data)
{
	int c;

	c = state->specifier;
	if ((state->flags & M_FLAG_HASH) == M_FLAG_HASH && *data != '0')
	{
		if (c == 'o' || c == 'O')
			return ("0");
		else if (c == 'x' || c == 'p')
			return ("0x");
		else if (c == 'X')
			return ("0X");
	}
	return ("");
}

int		ft_pf_get_pad_length(t_pf_state *state, t_pf_data *data)
{
	int width;

	width = state->width - (data->vlen + ft_strlen(data->sign) + ft_strlen(data->base_padding));
	return ((width > 0) ? width : 0);
}
