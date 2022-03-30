/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration_burning_ship.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:33:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 11:34:12 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Multiplies 2 complex numbers absolute values.
*/
static t_complex	ft_complex_square_abs(t_complex a)
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

/*
 * Iterates given complex number through Burning Ship function.
*/
int	fractal_iterate_burning_ship(t_complex z, t_complex c, int iterations)
{
	int			i;
	t_complex	value;

	(void)c;
	i = 0;
	value.real = 0;
	value.imaginary = 0;
	while (i < iterations
		&& value.real <= 2
		&& value.imaginary <= 2
		&& value.real * value.real + value.imaginary * value.imaginary <= 4)
	{
		value = ft_complex_square_abs(value);
		value.real = value.real + z.real;
		value.imaginary = value.imaginary + z.imaginary;
		i++;
	}
	return (i);
}
