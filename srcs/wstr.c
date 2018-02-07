/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:09:16 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/06 22:03:41 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char    *ft_wstoa(wchar_t *wstr)
{
	char *str;
	int i;

	str = ft_strnew(ft_wstr_len(wstr));
	i = -1;
	while (wstr[++i])
		str = ft_strjoin_free(str, ft_wtoa(wstr[i]));
	return (str);
}

char	*ft_wstoa_n(wchar_t *wstr, size_t n)
{
	char *str;
	int i;
	size_t len;
	size_t max;

	max = ft_wstr_len(wstr);
	if (n > max)
		n = max;
	str = ft_strnew(n);
	i = -1;
	len = 0;
	while (wstr[++i])
	{
		len += ft_wchar_len(wstr[i]);
		if (len > n)
			return (str);
		ft_strcat(str, ft_wtoa(wstr[i]));
	}
	return (str);
}
