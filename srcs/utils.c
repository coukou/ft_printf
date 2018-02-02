/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:20:15 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 15:32:43 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char    *extract_sign(t_pf_state *state, char **data)
{
	(void)state;
	char *tmp;

	if (**data == '-')
	{
		tmp = ft_strdup(*data + 1);
		ft_strdel(data);
		*data = tmp;
		return (ft_strdup("-"));
	}
	if ((state->flags & M_FLAG_PLUS) == M_FLAG_PLUS && state->specifier != 'u')
		return (ft_strdup("+"));
	if ((state->flags & M_FLAG_SPACE) == M_FLAG_SPACE && state->specifier != 'u')
		return (ft_strdup(" "));
	return (ft_strnew(0));
}

char		*ft_pf_get_base(int c)
{
	if (c == 'o' || c == 'O')
		return ("01234567");
	else if (c == 'x')
		return ("0123456789abcdef");
	else if (c == 'X')
		return ("0123456789ABCDEF");
	else
		return ("0123456789");
}

char		*ft_pf_get_base_padding(t_pf_state *state, char *data)
{
	int c;

	c = state->specifier;
	if ((state->flags & M_FLAG_HASH) == M_FLAG_HASH && *data != '0')
	{
		if (c == 'o' || c == 'O')
			return ("0");
		else if (c == 'x')
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
