/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:08:57 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/26 19:01:29 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>
#include <wchar.h>

int		ft_printf(const char *format, ...);

int main()
{
	setlocale(LC_ALL, "");

	printf("%d\n", printf("%C", L'ሴ'));
	printf("%d\n", ft_printf("%C", L'ሴ'));
	return (0);
}
