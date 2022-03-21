/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:39:26 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/21 17:18:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* static double	ft_complex_abs(t_complex a)
{
	return (sqrt(a.real * a.real + a.imaginary * a.imaginary));
} */

static t_complex	ft_complex_plus(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real + b.real;
	result.imaginary = a.imaginary + b.imaginary;
	return (result);
}

/*
 * (x + yi)(u + vi) = (xu - yv) + (xv + yu)i
*/
static t_complex	ft_complex_multiply(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real * b.real - a.imaginary * b.imaginary;
	result.imaginary = a.real * b.imaginary + a.imaginary * b.real;
	return (result);
}

/*
 * Iterates given complex number through Mandelbrot function. A point belongs
 * to Mandelbrot set if its absolute value is less or equal than 2 (sqrt of 4).
*/
int	fractal_iterate_mandelbrot(t_complex z)
{
	int			i;
	t_complex	value;

	i = 0;
	value.real = 0;
	value.imaginary = 0;
	while (i < MAX_ITERATIONS
		&& value.real * value.real + value.imaginary * value.imaginary <= 4)
	{
		value = ft_complex_plus(ft_complex_multiply(value, value), z);
		i++;
	}
	return (i);
}
