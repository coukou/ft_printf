/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:04:23 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 18:22:01 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char     *wtoa_1(wchar_t wchar)
{
	char *ret;

	ret = ft_strnew(1);
	ret[0] = wchar & 0x7F;
	return (ret);
}

static char    *wtoa_2(wchar_t wchar)
{
	char *ret;

	ret = ft_strnew(2);
	ret[0] = 0xC0 | ((wchar >> 6) & 0x1F);
	ret[1] = 0x80 | (wchar & 0x3F);
	return (ret);
}

static char    *wtoa_3(wchar_t wchar)
{
	char *ret;

	ret = ft_strnew(3);
	ret[0] = 0xE0 | ((wchar >> 12) & 0xF);
	ret[1] = 0x80 | ((wchar >> 6) & 0x3F);
	ret[2] = 0x80 | (wchar & 0x3F);
	return (ret);
}

static char     *wtoa_4(wchar_t wchar)
{
	char *ret;

	ret = ft_strnew(4);
	ret[0] = 0xF0 | ((wchar >> 18) & 0x7);
	ret[1] = 0x80 | ((wchar >> 12) & 0x3F);
	ret[2] = 0x80 | ((wchar >> 6) & 0x3F);
	ret[3] = 0x80 | (wchar & 0x3F);
	return (ret);
}

char            *ft_wtoa(wchar_t wchar)
{
	int wlen;

	wlen = ft_wchar_len(wchar);
	if (wlen == 1)
		return (wtoa_1(wchar));
	if (wlen == 2)
		return (wtoa_2(wchar));
	if (wlen == 3)
		return (wtoa_3(wchar));
	if (wlen == 4)
		return (wtoa_4(wchar));
	return (NULL);
}
