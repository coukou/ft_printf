/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:01:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/22 16:24:24 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_s_specifier(const char **buf, va_list args)
{
	(void)buf;
	ft_putstr(va_arg(args, char*));
}

void	ft_d_specifier(const char **buf, va_list args)
{
	(void)buf;
	ft_putnbr(va_arg(args, int));
}

void	ft_u_specifier(const char **buf, va_list args)
{
	(void)buf;
	ft_putnbr(va_arg(args, unsigned int));
}

void	ft_percent_specifier(const char **buf, va_list args)
{
	(void)buf;
	(void)args;
	ft_putchar('%');
}
