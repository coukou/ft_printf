/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:01:20 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/22 16:22:17 by spopieul         ###   ########.fr       */
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
void	ft_d_specifier(int c, t_pf_state *state);
void	ft_u_specifier(int c, t_pf_state *state);
void	ft_oxX_specifier(int c, t_pf_state *state);
// void	ft_f_specifier(int c, t_pf_state *state);
// void	ft_F_specifier(int c, t_pf_state *state);
// void	ft_e_specifier(int c, t_pf_state *state);
// void	ft_E_specifier(int c, t_pf_state *state);
// void	ft_g_specifier(int c, t_pf_state *state);
// void	ft_G_specifier(int c, t_pf_state *state);
// void	ft_a_specifier(int c, t_pf_state *state);
// void	ft_A_specifier(int c, t_pf_state *state);
// void	ft_c_specifier(int c, t_pf_state *state);
// void	ft_s_specifier(int c, t_pf_state *state);
// void	ft_p_specifier(int c, t_pf_state *state);
// void	ft_n_specifier(int c, t_pf_state *state);
void	ft_percent_specifier(int c, t_pf_state *state);

t_specifier_handler specifier_handler[] = {
	{ 's', &ft_s_specifier },
	{ 'd', &ft_d_specifier },
	{ 'i', &ft_d_specifier },
	{ 'u', &ft_u_specifier },
	{ 'o', &ft_oxX_specifier },
	{ 'x', &ft_oxX_specifier },
	{ 'X', &ft_oxX_specifier },
	// { 'f', &ft_f_specifier },
	// { 'F', &ft_F_specifier },
	// { 'e', &ft_e_specifier },
	// { 'E', &ft_E_specifier },
	// { 'g', &ft_g_specifier },
	// { 'G', &ft_G_specifier },
	// { 'a', &ft_a_specifier },
	// { 'A', &ft_A_specifier },
	// { 'c', &ft_c_specifier },
	// { 's', &ft_s_specifier },
	// { 'p', &ft_p_specifier },
	// { 'n', &ft_n_specifier },
	{ '%', &ft_percent_specifier },
	{ 0, 0 }
};

#endif
