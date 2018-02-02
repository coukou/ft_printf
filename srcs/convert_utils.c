/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:23:13 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 11:27:25 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_ultoa(unsigned long long n, char *base)
{
	int i;
	char *ret;
	size_t base_len;

	base_len = ft_strlen(base);
	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	ret = ft_strnew(64);
	while (n)
	{
		ret[i++] = base[n % base_len];
		n /= base_len;
	}
	return (ft_strrev(ret));
}

char	*ft_ltoa(long long n)
{
	char *ret;

	if (n == 0)
		return (ft_strdup("0"));
	ret = ft_ultoa(((n < 0) ? -n : n), "0123456789");
	if (n < 0)
		return (ft_strjoin_free(ft_strdup("-"), ret));
	return (ret);
}
