/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:51:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 13:52:26 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pf_get_flag(int c)
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

int		ft_pf_get_length(int c)
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
