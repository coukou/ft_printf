/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:48:16 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 21:08:22 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_buffer_flush(t_pf_buffer *buffer)
{
	if (buffer->content_size == 0)
		return ;
	write(1, buffer->data, buffer->content_size);
	buffer->content_size = 0;
}

void	ft_pf_buffer_write_n(t_pf_buffer *buffer, char *data, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (buffer->content_size == PRINTF_BUFF_SIZE)
			ft_pf_buffer_flush(buffer);
		buffer->data[buffer->content_size++] = ((unsigned char*)data)[i++];
		buffer->writed++;
	}
}

void	ft_pf_buffer_write(t_pf_buffer *buffer, char *data)
{
	ft_pf_buffer_write_n(buffer, data, ft_strlen((const char*)data));
}
