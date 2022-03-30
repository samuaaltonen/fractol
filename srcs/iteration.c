/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:39:26 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 11:02:41 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static t_complex	newton_poly_div_1(t_complex z)
{
	t_complex	a;
	t_complex	b;

	a = ft_complex_power(z, 3);
	b = ft_complex_square(z);
	a.real -= 1;
	b.real *= 3;
	b.imaginary *= 3;
	return (ft_complex_divide(a, b));
}

/*
 * Iterates given complex number through generalized Newton fractal function,
 * with polynomial z^3 - 1.
 * Breaks the iteration loop when z gets near any root of polynomial z^3 - 1.
 * 
 * Roots: 1, -1/2 + sqrt(3)i/2, -1/2 - sqrt(3)i/2 
*/
int	fractal_iterate_newton_poly_1(t_complex z, t_complex c, int iterations)
{
	int			i;
	t_complex	poly;

	(void)c;
	i = 0;
	while (i < iterations)
	{
		if ((ft_abs_ldouble(z.real - 1) < 0.01L && ft_abs_ldouble(z.imaginary) < 0.01L))
			return (iterations / 3);
		if ((ft_abs_ldouble(z.real + 0.5L) < 0.01L && ft_abs_ldouble(z.imaginary - 0.866025403784439L) < 0.01L))
			return (iterations / 3 * 2);
		if ((ft_abs_ldouble(z.real + 0.5L) < 0.01L && ft_abs_ldouble(z.imaginary + 0.866025403784439L) < 0.01L))
			return (iterations - 1);
		poly = newton_poly_div_1(z);
		z.real = z.real - poly.real;
		z.imaginary = z.imaginary - poly.imaginary;
		i++;
	}
	return (i);
}
