/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:39:26 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 18:52:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Multiplies 2 complex numbers.
*/
static t_complex	ft_complex_square(t_complex a)
{
	t_complex	result;

	result.real = a.real * a.real - a.imaginary * a.imaginary;
	result.imaginary = a.real * a.imaginary + a.imaginary * a.real;
	return (result);
}

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

/*
 * Iterates given complex number through Julia function.
*/
int	fractal_iterate_julia(t_complex z, t_complex c, int iterations)
{
	int			i;

	i = 0;
	while (i < iterations
		&& z.real <= 2
		&& z.imaginary <= 2
		&& z.real * z.real + z.imaginary * z.imaginary <= 4)
	{
		z = ft_complex_square(z);
		z.real = z.real + c.real;
		z.imaginary = z.imaginary + c.imaginary;
		i++;
	}
	return (i);
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
