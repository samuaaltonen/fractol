/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_divide.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:38:47 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 10:38:57 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Divides 2 comlex numbers. Uses formula:
 * (a + bi) / (c + di) = (ac + bd) / (c^2 + d^2) + (bc - ad)i / (c^2 + d^2)
*/
t_complex	ft_complex_divide(t_complex num, t_complex denum)
{
	long double	real;
	long double	imaginary;

	real = (num.real * denum.real + num.imaginary * denum.imaginary) /
			(denum.real * denum.real + denum.imaginary * denum.imaginary);
	imaginary = (num.imaginary * denum.real - num.real * denum.imaginary) /
			(denum.real * denum.real + denum.imaginary * denum.imaginary);
	return ((t_complex){real, imaginary});
}
