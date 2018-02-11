/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:06:25 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 18:16:32 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     ft_wchar_len(wchar_t wchar)
{
    if (wchar >= 0x00 && wchar <= 0x7F)
        return (1);
    else if (wchar >= 0x80 && wchar <= 0x7FF)
        return (2);
    else if (wchar >= 0x800 && wchar <= 0xFFFF)
        return (3);
    else if (wchar >= 0x10000 && wchar <= 0x10FFFF)
        return (4);
    return (0);
}

int    ft_wstr_len(wchar_t *wstr)
{
    int len;
    int i;

    i = -1;
    len = 0;
    while (wstr[++i])
        len += ft_wchar_len(wstr[i]);
    return (len);
}
