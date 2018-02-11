/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:08:57 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 19:39:38 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <math.h>

int		ft_printf(const char *format, ...);

int main()
{
	int ret;
	// setlocale(LC_ALL, "");

	ret = ft_printf("%-050d\n", -42);
	ft_printf("%d\n", ret);
	ret = printf("%-050d\n", -42);
	printf("%d\n", ret);
	// printf("%-050.50s\n", "salut");
	// printf("%-010s\n", "salut");
	// printf("ft: %d\n", ret);
	// ret = printf("%-10s\n", "salut");
	// printf("pf: %d\n", ret);
	// ft_printf("\n");
	// ret = ft_printf("salutlol\n");
	// ft_printf("%d\n", ret);
	// ft_printf("%%\n");
	// ft_printf("%d\n", 42);
	// ft_printf("%d%d\n", 42, 41);
	// ft_printf("%d%d%d\n", 42, 43, 44);
	// ft_printf("%ld\n", 2147483647);
	// ft_printf("%lld\n", 9223372036854775807);
	// ft_printf("%x\n", 505);
	// ft_printf("%X\n", 505);
	// ft_printf("%p\n", &ft_printf);
	// ft_printf("%20.15d\n", 54321);
	// ft_printf("%-10d\n", 3);
	// ft_printf("% d\n", 3);
	// ft_printf("%+d\n", 3);
	// ft_printf("%010d\n", 1);
	// ft_printf("%hhd\n", 0);
	// ft_printf("%jd\n", 9223372036854775807);
	// ft_printf("%zd\n", 4294967295);
	// ft_printf("%\n");
	// ft_printf("%b\n", 42);
	// ft_printf("%U\n", 4294967295);
	// ft_printf("%u\n", 4294967295);
	// ft_printf("%o\n", 40);
	// ft_printf("%%#08x\n", 42);
	// ft_printf("%x\n", 1000);
	// ft_printf("%#X\n", 1000);
	// ft_printf("%s\n", NULL);
	// ft_printf("%S\n", L"ݗݜशব");
	// ft_printf("%S\n", L"😻");
	// ft_printf("%C\n", L'😻');
	// ft_printf("%s%s\n", "test", "test");
	// ft_printf("%s%s%s\n", "test", "test", "test");
	// ft_printf("%C\n", 15000);
	// ft_printf("%-10x\n", 10, 9223372036854775807);
	// printf("%-10x\n",10, 9223372036854775807);
	// printf("%l#x\n", 9223372036854775807);

	// ft_printf("\n");
	// ret = printf("\033[1;4mHello\033[24mWorld\n");
	// ft_printf("%hd%hd\n", 97897897879486, 97897897879486);
	return (0);
}
