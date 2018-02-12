/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:35:50 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:28:33 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/string.h"

static char		*wctoa_1(wchar_t wc)
{
	char *ret;

	ret = ft_strnew(1);
	ret[0] = wc & 0x7F;
	return (ret);
}

static char		*wctoa_2(wchar_t wc)
{
	char *ret;

	ret = ft_strnew(2);
	ret[0] = 0xC0 | ((wc >> 6) & 0x1F);
	ret[1] = 0x80 | (wc & 0x3F);
	return (ret);
}

static char		*wctoa_3(wchar_t wc)
{
	char *ret;

	ret = ft_strnew(3);
	ret[0] = 0xE0 | ((wc >> 12) & 0xF);
	ret[1] = 0x80 | ((wc >> 6) & 0x3F);
	ret[2] = 0x80 | (wc & 0x3F);
	return (ret);
}

static char		*wctoa_4(wchar_t wc)
{
	char *ret;

	ret = ft_strnew(4);
	ret[0] = 0xF0 | ((wc >> 18) & 0x7);
	ret[1] = 0x80 | ((wc >> 12) & 0x3F);
	ret[2] = 0x80 | ((wc >> 6) & 0x3F);
	ret[3] = 0x80 | (wc & 0x3F);
	return (ret);
}

char			*ft_wctoa(wchar_t wc)
{
	int wlen;

	wlen = ft_wclen(wc);
	if (wlen == 1)
		return (wctoa_1(wc));
	if (wlen == 2)
		return (wctoa_2(wc));
	if (wlen == 3)
		return (wctoa_3(wc));
	if (wlen == 4)
		return (wctoa_4(wc));
	return (NULL);
}
