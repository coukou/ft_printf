/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:46:39 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/22 17:09:03 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct	s_pf_state
{
	char	flags[32];
	size_t	precision;
	size_t	width;
	char	length[32];
}				t_pf_state;

int		ft_printf(const char *fmt, ...);

#endif
