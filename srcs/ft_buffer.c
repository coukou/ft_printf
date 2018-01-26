/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:48:16 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/26 14:17:00 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    ft_printf_buffer_flush(t_printf_buffer *buffer)
{
    if (buffer->content_size == 0)
        return ;
    write(1, buffer->data, buffer->content_size);
    buffer->writed += buffer->content_size;
    buffer->content_size = 0;
}

void    ft_printf_buffer_write(t_printf_buffer *buffer, char *data, size_t size)
{
    while (size-- > 0)
    {
        if (buffer->content_size == PRINTF_BUFF_SIZE)
            ft_printf_buffer_flush(buffer);
        buffer->data[buffer->content_size++] = *(data++);
    }
}
