/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:26:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:26:17 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isblank(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
