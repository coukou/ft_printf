/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:08:57 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/29 14:13:18 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <math.h>

int		ft_printf(const char *format, ...);

double	ft_pow(double nb, int power)
{
	int i;
	double res;

	i = -1;
	res = 1;
	if (nb < 0)
		return (0);
	while (++i < power)
		res *= nb;
	return (res);
}

static char	*generate_zero_padding(size_t width)
{
	char *pad;

	pad = ft_strnew(width);
	ft_memset(pad, '0', width);
	return (pad);
}

double	ft_round(double n, int precision)
{
	double factor;
	double tmp;
	int neg;

	neg = (n < 0) ? -1 : 1;
	n = (n < 0) ? -n : n;
	factor = ft_pow(10, precision);
	tmp = n - (int)n;
	if ((((int)(tmp * (factor * 10))) % 10) >= 5)
		n += (0.5 / factor);
	return (n * neg);
}

char	*ft_dtoa(double n, int precision)
{
	char *data;
	long ipart;
	double fpart;
	int fpart_len;
	char *afpart;

	n = ft_round(n, precision);
	ipart = (int)n;
	fpart = (n - ipart) * ft_pow(10, precision);
	fpart = (fpart < 0) ? -fpart : fpart;
	data = ft_itoa(ipart);
	// if (fpart > 0)
	// {
	// 	afpart = ft_itoa(fpart);
	// 	data = ft_strjoin_free(data, ft_strdup("."));
	// 	fpart_len = ft_strlen(afpart);
	// 	if (fpart_len < precision)
	// 		data = ft_strjoin_free(data, generate_zero_padding(precision - fpart_len));
	// 	data = ft_strjoin_free(data, afpart);
	// }
	return (data);
}

int main()
{
	// setlocale(LC_ALL, "");

	// int precision = 10;
	// double n = 1337.06596456789;
	int res;
	ft_printf("ft_printf	");
	res = ft_printf("@moulitest: %#.o %#.0o", 0, 0);
	ft_printf(" :: (%d)\n", res);
	ft_printf("printf		");
	res = printf("@moulitest: %#.o %#.0o", 0, 0);
	printf(" :: (%d)\n", res);
	// printf("%s\n", ft_dtoa(n, precision));
	return (0);
}
