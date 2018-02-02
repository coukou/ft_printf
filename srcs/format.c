/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:18:26 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/02 15:48:03 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ppad_data(t_pf_state *state, char *data)
{
	char *padding;
	int width;

	width = state->precision - ft_strlen(data);
	if (width < 0)
		return (data);
	padding = ft_strnew(width);
	ft_memset(padding, '0', width);
	return (ft_strjoin_free(padding, data));
}

t_pf_data	*ft_format_diuoxX(t_pf_state *state, char *data_tmp)
{
	t_pf_data *data;

	data = ft_create_data();
	data->sign = extract_sign(state, &data_tmp);
	data->base_padding = ft_pf_get_base_padding(state, data_tmp);
	if (state->precision == 0 && *data_tmp == '0')
	{
		if ((state->flags & M_FLAG_HASH) == M_FLAG_HASH &&  state->specifier == 'o')
			data->value = data_tmp;
		else
		{
			ft_strdel(&data_tmp);
			data->value = ft_strnew(0);
		}
	}
	else
		data->value = ppad_data(state, data_tmp);
	data->vlen = ft_strlen(data->value);
	return (data);
}

static char	*generate_padding(int c, int len)
{
	char *padding;

	if (len < 0)
		return (ft_strnew(0));
	padding = ft_strnew(len);
	ft_memset(padding, c, len);
	return (padding);
}

void	write_data(t_pf_state *state, t_pf_data *data, t_pf_buffer *pbuff)
{
	size_t pad_len;
	char *padding;

	pad_len = ft_pf_get_pad_length(state, data);
	if (data->pad_char == 0)
		data->pad_char = ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO && state->precision < 0) ? '0' : ' ';
	if ((state->flags & M_FLAG_MINUS) == M_FLAG_MINUS)
	{
		padding = generate_padding(' ', pad_len);
		ft_pf_buffer_write(pbuff, (unsigned char*)data->sign);
		ft_pf_buffer_write(pbuff, (unsigned char*)data->base_padding);
		ft_pf_buffer_write_n(pbuff, (unsigned char*)data->value, data->vlen);
		ft_pf_buffer_write(pbuff, (unsigned char*)padding);
	}
	else
	{
		padding = generate_padding(data->pad_char, pad_len);
		if (data->pad_char == '0')
		{
			ft_pf_buffer_write(pbuff, (unsigned char*)data->base_padding);
			ft_pf_buffer_write(pbuff, (unsigned char*)data->sign);
			ft_pf_buffer_write(pbuff, (unsigned char*)padding);
		}
		if (data->pad_char != '0')
		{
			ft_pf_buffer_write(pbuff, (unsigned char*)padding);
			ft_pf_buffer_write(pbuff, (unsigned char*)data->sign);
			ft_pf_buffer_write(pbuff, (unsigned char*)data->base_padding);
		}
		ft_pf_buffer_write_n(pbuff, (unsigned char*)data->value, data->vlen);
	}
	ft_strdel(&padding);
}
