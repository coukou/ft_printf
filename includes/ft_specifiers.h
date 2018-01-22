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

typedef struct s_specifier_handler
{
	int c;
	void (*f)(const char**, va_list);
}				t_specifier_handler;

void	ft_s_specifier(const char **buf, va_list args);
void	ft_d_specifier(const char **buf, va_list args);
void	ft_u_specifier(const char **buf, va_list args);
// void	ft_o_specifier(const char **buf, va_list args);
// void	ft_x_specifier(const char **buf, va_list args);
// void	ft_X_specifier(const char **buf, va_list args);
// void	ft_f_specifier(const char **buf, va_list args);
// void	ft_F_specifier(const char **buf, va_list args);
// void	ft_e_specifier(const char **buf, va_list args);
// void	ft_E_specifier(const char **buf, va_list args);
// void	ft_g_specifier(const char **buf, va_list args);
// void	ft_G_specifier(const char **buf, va_list args);
// void	ft_a_specifier(const char **buf, va_list args);
// void	ft_A_specifier(const char **buf, va_list args);
// void	ft_c_specifier(const char **buf, va_list args);
// void	ft_s_specifier(const char **buf, va_list args);
// void	ft_p_specifier(const char **buf, va_list args);
// void	ft_n_specifier(const char **buf, va_list args);
void	ft_percent_specifier(const char **buf, va_list args);

t_specifier_handler specifier_handler[] = {
	{ 's', &ft_s_specifier },
	{ 'd', &ft_d_specifier },
	{ 'i', &ft_d_specifier },
	{ 'u', &ft_u_specifier },
	// { 'o', &ft_o_specifier },
	// { 'x', &ft_x_specifier },
	// { 'X', &ft_X_specifier },
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
