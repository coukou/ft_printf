/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:28:33 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:30:08 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/string.h"
#include "libft/conversion.h"
#include "libft/memory.h"

static size_t	get_final_size(const wchar_t *wstr)
{
	int		i;
	size_t	len;

	i = -1;
	len = 0;
	while (wstr[++i])
		len += ft_wclen(wstr[i]);
	return (len);
}

char			*ft_wstrtoa(const wchar_t *wstr)
{
	char	*str;
	int		i;
	size_t	offset;
	size_t	wc_len;

	str = ft_strnew(get_final_size(wstr));
	if (!str)
		return (NULL);
	i = -1;
	offset = 0;
	while (wstr[++i])
	{
		wc_len = ft_wclen(wstr[i]);
		ft_memcpy(str + offset, ft_wctoa(wstr[i]), wc_len);
		offset += wc_len;
	}
	return (str);
}
