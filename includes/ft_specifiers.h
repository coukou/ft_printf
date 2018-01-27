/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:01:20 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/26 17:46:40 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPECIFIERS_H
# define FT_SPECIFIERS_H

#include "ft_printf.h"

typedef struct s_specifier_handler
{
	int c;
	void (*f)(int, t_pf_state*);
}				t_specifier_handler;

void	ft_s_specifier(int c, t_pf_state *state);
void	ft_di_specifier(int c, t_pf_state *state);
void	ft_u_specifier(int c, t_pf_state *state);
void	ft_uoxX_specifier(int c, t_pf_state *state);
// void	ft_f_specifier(int c, t_pf_state *state);
// void	ft_F_specifier(int c, t_pf_state *state);
// void	ft_e_specifier(int c, t_pf_state *state);
// void	ft_E_specifier(int c, t_pf_state *state);
// void	ft_g_specifier(int c, t_pf_state *state);
// void	ft_G_specifier(int c, t_pf_state *state);
// void	ft_a_specifier(int c, t_pf_state *state);
// void	ft_A_specifier(int c, t_pf_state *state);
void	ft_c_specifier(int c, t_pf_state *state);
void	ft_C_specifier(int c, t_pf_state *state);
// void	ft_s_specifier(int c, t_pf_state *state);
void	ft_p_specifier(int c, t_pf_state *state);
// void	ft_n_specifier(int c, t_pf_state *state);
void	ft_percent_specifier(int c, t_pf_state *state);

t_specifier_handler specifier_handler[] = {
	{ 's', &ft_s_specifier },
	{ 'd', &ft_di_specifier },
	{ 'i', &ft_di_specifier },
	{ 'u', &ft_uoxX_specifier },
	{ 'o', &ft_uoxX_specifier },
	{ 'x', &ft_uoxX_specifier },
	{ 'X', &ft_uoxX_specifier },
	// { 'f', &ft_f_specifier },
	// { 'F', &ft_F_specifier },
	// { 'e', &ft_e_specifier },
	// { 'E', &ft_E_specifier },
	// { 'g', &ft_g_specifier },
	// { 'G', &ft_G_specifier },
	// { 'a', &ft_a_specifier },
	// { 'A', &ft_A_specifier },
	{ 'c', &ft_c_specifier },
	{ 'C', &ft_C_specifier },
	// { 's', &ft_s_specifier },
	{ 'p', &ft_p_specifier },
	// { 'n', &ft_n_specifier },
	{ '%', &ft_percent_specifier },
	{ 0, 0 }
};

#endif
