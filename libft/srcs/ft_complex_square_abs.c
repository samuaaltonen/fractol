/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_square_abs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:38:15 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 10:38:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Multiplies 2 complex numbers absolute values.
*/
t_complex	ft_complex_square_abs(t_complex a)
{
	t_complex	result;

	if (a.real < 0)
		a.real = -a.real;
	if (a.imaginary < 0)
		a.imaginary = -a.imaginary;
	result.real = a.real * a.real - a.imaginary * a.imaginary;
	result.imaginary = a.real * a.imaginary + a.imaginary * a.real;
	return (result);
}
