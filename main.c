/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:08:57 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/26 15:04:35 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...);

int main()
{
	int i;

	printf("%d\n", printf("%p", &i));
	printf("%d\n", ft_printf("%p", &i));
	return (0);
}
