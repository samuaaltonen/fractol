/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:21:04 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/19 13:21:31 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}