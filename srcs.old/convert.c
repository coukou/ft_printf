/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:01:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:44:15 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_pf_data	*ft_create_data()
{
	t_pf_data *data;

	if (!(data = (t_pf_data*)ft_memalloc(sizeof(*data))))
		return (NULL);
	data->base_padding = "";
	data->sign = "";
	data->value = "";
	data->vlen = 0;
	return (data);
}


t_pf_data	*ft_pf_get_S(t_pf_state *state)
{
	t_pf_data *data;
	wchar_t *tmp;

	data = ft_create_data();
	tmp = va_arg(*state->args, wchar_t*);
	if (tmp == 0)
		tmp = L"(null)";
	if (state->precision < 0)
		data->value = ft_wstrtoa(tmp);
	else
		data->value = ft_wstrtoa_n(tmp, state->precision);
	if ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO
	&& ((state->flags & M_FLAG_MINUS) != M_FLAG_MINUS))
		data->pad_char = '0';
	else
		data->pad_char = ' ';
	data->vlen = ft_strlen(data->value);
	return (data);
}

t_pf_data	*ft_pf_get_p(t_pf_state *state)
{
	intptr_t tmp;
	char *base;
	t_pf_data *data;

	data = ft_create_data();
	tmp = va_arg(*state->args, intptr_t);
	base = ft_pf_get_base(state);
	data->base_padding = "0x";
	if (tmp == 0)
		data->value = ft_strdup((state->precision < 0) ? "0" : "");
	else
		data->value = ft_ultoa(tmp, base);
	data->value = ppad_data(state, data->value, data->base_padding);
	data->vlen = ft_strlen(data->value);
	ft_strdel(&base);
	return (data);
}

t_pf_data	*ft_pf_get_s(t_pf_state *state)
{
	t_pf_data *data;
	char *tmp;

	if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		return (ft_pf_get_S(state));
	data = ft_create_data();
	tmp = va_arg(*state->args, char*);
	if (tmp == 0)
		tmp = "(null)";
	if (state->precision < 0)
		data->value = ft_strdup(tmp);
	else
		data->value = ft_strndup(tmp, state->precision);
	if ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO
	&& ((state->flags & M_FLAG_MINUS) != M_FLAG_MINUS))
		data->pad_char = '0';
	else
		data->pad_char = ' ';
	data->vlen = ft_strlen(data->value);
	return (data);
}

t_pf_data	*ft_pf_get_C(t_pf_state *state)
{
	t_pf_data *data;
	wchar_t tmp;

	data = ft_create_data();

	tmp = va_arg(*state->args, wchar_t);
	data->value = ft_wtoa(tmp);
	data->vlen = ft_wchar_len(tmp);
	return (data);
}

t_pf_data	*ft_pf_get_c(t_pf_state *state)
{
	t_pf_data *data;
	char tmp;

	if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		return (ft_pf_get_C(state));
	data = ft_create_data();
	if ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO)
		data->pad_char = '0';
	tmp = va_arg(*state->args, int);
	data->value = ft_strnew(1);
	data->value[0] = tmp;
	data->vlen = 1;
	return (data);
}

t_pf_data	*ft_pf_get_percent(t_pf_state *state)
{
	(void)state;
	t_pf_data *data;

	data = ft_create_data();
	if ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO)
		data->pad_char = '0';
	data->value = ft_strdup("%");
	data->vlen = 1;
	return (data);
}

t_pf_data	*ft_pf_get_unknown(t_pf_state *state)
{
	(void)state;
	t_pf_data *data;

	data = ft_create_data();
	if ((state->flags & M_FLAG_ZERO) == M_FLAG_ZERO)
		data->pad_char = '0';
	data->value = ft_strdup((const char*)&state->specifier);
	data->vlen = 1;
	return (data);
}

t_pf_data	*ft_pf_get_di(t_pf_state *state)
{
	char *data;

	if ((state->length & M_LENGTH_LL) == M_LENGTH_LL)
		data = ft_ltoa((long long)va_arg(*state->args, long long));
	else if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		data = ft_ltoa((long)va_arg(*state->args, long));
	else if ((state->length & M_LENGTH_HH) == M_LENGTH_HH)
		data = ft_ltoa((char)va_arg(*state->args, int));
	else if ((state->length & M_LENGTH_H) == M_LENGTH_H)
		data = ft_ltoa((short)va_arg(*state->args, int));
	else if ((state->length & M_LENGTH_J) == M_LENGTH_J)
		data = ft_ltoa(va_arg(*state->args, intmax_t));
	else if ((state->length & M_LENGTH_Z) == M_LENGTH_Z)
		data = ft_ltoa(va_arg(*state->args, size_t));
	else if ((state->length & M_LENGTH_T) == M_LENGTH_T)
		data = ft_ltoa(va_arg(*state->args, long));
	else
		data = ft_ltoa(va_arg(*state->args, int));
	return (ft_format_diuoxX(state, data));
}

t_pf_data	*ft_pf_get_uoxX(t_pf_state *state)
{
	char *data;
	char *base;

	base = ft_pf_get_base(state);
	if ((state->length & M_LENGTH_LL) == M_LENGTH_LL)
		data = ft_ultoa((unsigned long long)va_arg(*state->args, unsigned long long), base);
	else if ((state->length & M_LENGTH_L) == M_LENGTH_L)
		data = ft_ultoa((unsigned long)va_arg(*state->args, unsigned long), base);
	else if ((state->length & M_LENGTH_HH) == M_LENGTH_HH)
		data = ft_ultoa((unsigned char)va_arg(*state->args, unsigned int), base);
	else if ((state->length & M_LENGTH_H) == M_LENGTH_H)
		data = ft_ultoa((unsigned short)va_arg(*state->args, unsigned int), base);
	else if ((state->length & M_LENGTH_J) == M_LENGTH_J)
		data = ft_ultoa(va_arg(*state->args, uintmax_t), base);
	else if ((state->length & M_LENGTH_Z) == M_LENGTH_Z)
		data = ft_ultoa(va_arg(*state->args, size_t), base);
	else if ((state->length & M_LENGTH_T) == M_LENGTH_T)
		data = ft_ultoa(va_arg(*state->args, long), base);
	else
		data = ft_ultoa(va_arg(*state->args, unsigned int), base);
	ft_strdel(&base);
	return (ft_format_diuoxX(state, data));
}
