/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration_mandelbrot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:32:16 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 12:49:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Squares a complex number.
*/
static t_complex	ft_complex_square(t_complex a)
{
	t_complex	result;

	result.real = a.real * a.real - a.imaginary * a.imaginary;
	result.imaginary = a.real * a.imaginary + a.imaginary * a.real;
	return (result);
}

/*
 * Iterates given complex number through Mandelbrot function. A point belongs
 * to Mandelbrot set if its absolute value is less or equal than 2 (sqrt of 4).
*/
int	fractal_iterate_mandelbrot(t_complex z, t_complex c, int iterations)
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
		value = ft_complex_square(value);
		value.real = value.real + z.real;
		value.imaginary = value.imaginary + z.imaginary;
		i++;
	}
	return (i);
}
