/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_power.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:39:11 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 11:03:22 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Raises a complex number to given power. Supports only positive integer
 * type exponents.
*/
t_complex	ft_complex_power(t_complex a, int pow)
{
	t_complex	result;
	int			i;

	if (pow <= 0)
	{
		result.real = 0;
		result.imaginary = 0;
		return (result);
	}
	result.real = a.real;
	result.imaginary = a.imaginary;
	i = 1;
	while (i < pow)
	{
		result = ft_complex_multiply(result, a);
		i++;
	}
	return (result);
}
