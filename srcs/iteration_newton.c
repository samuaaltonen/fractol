/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration_newton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:39:26 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 11:57:53 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Multiplies 2 complex numbers.
*/
static t_complex	ft_complex_multiply(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real * b.real - a.imaginary * b.imaginary;
	result.imaginary = a.real * b.imaginary + a.imaginary * b.real;
	return (result);
}

/*
 * Raises a complex number to given power. Supports only positive integer
 * type exponents.
*/
static t_complex	ft_complex_power(t_complex a, int pow)
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

static t_complex	newton_poly_div_1(t_complex z)
{
	t_complex	a;
	t_complex	b;
	long double	real;
	long double	imaginary;

	a = ft_complex_power(z, 3);
	b = ft_complex_square(z);
	a.real -= 1;
	b.real *= 3;
	b.imaginary *= 3;
	real = (a.real * b.real + a.imaginary * b.imaginary)
		/ (b.real * b.real + b.imaginary * b.imaginary);
	imaginary = (a.imaginary * b.real - a.real * b.imaginary)
		/ (b.real * b.real + b.imaginary * b.imaginary);
	return ((t_complex){real, imaginary});
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
		if (fabsl(z.real - 1) < 0.01L && fabsl(z.imaginary) < 0.01L)
			return (i);
		if (fabsl(z.real + 0.5L) < 0.01L && fabsl(z.imaginary - 0.866L) < 0.01L)
			return (i);
		if (fabsl(z.real + 0.5L) < 0.01L && fabsl(z.imaginary + 0.866L) < 0.01L)
			return (i);
		poly = newton_poly_div_1(z);
		z.real = z.real - poly.real;
		z.imaginary = z.imaginary - poly.imaginary;
		i++;
	}
	return (i);
}
