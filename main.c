/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:08:57 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/24 16:04:16 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...);

int main()
{
	printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, "salut", 100);
	ft_printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, "salut", 100);

	printf("%-5%, %05s, %010d, %x\n", "hello", 1337, 100);
	ft_printf("%-5%, %05s, %010d, %x\n", "hello", 1337, 100);
	return (0);
}
