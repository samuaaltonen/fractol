/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration_newton_hourglass.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:39:26 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 17:02:41 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Performs polynomial division for hourglass fractal. Polynomial is sin(z),
 * and its 1st derivative is cos(z).
 * 
 * sin(a + bi) = sin(a)cosh(b) + icos(a)sinh(b)
 * cos(a + bi) = cos(a)cosh(b) + isin(a)sinh(b)
*/
static t_complex	newton_poly_div_hourglass(t_complex z)
{
	t_complex	a;
	t_complex	b;
	long double	real;
	long double	imaginary;

	a = (t_complex){sin(z.real) * cosh(z.imaginary),
						cos(z.real) * sinh(z.imaginary)};
	b = (t_complex){cos(z.real) * cosh(z.imaginary),
						sin(z.real) * sinh(z.imaginary)};
	real = (a.real * b.real + a.imaginary * b.imaginary)
		/ (b.real * b.real + b.imaginary * b.imaginary);
	imaginary = (a.imaginary * b.real - a.real * b.imaginary)
		/ (b.real * b.real + b.imaginary * b.imaginary);
	return ((t_complex){real, imaginary});
}

/*
 * Iterates given complex number through generalized Newton fractal function,
 * with polynomial sin(z)
 * Breaks the iteration loop when z gets near any root (PI * n)
*/
int	fractal_iterate_newton_hourglass(t_complex z, t_complex c, int max)
{
	int			i;
	t_complex	poly;

	(void)c;
	i = 0;
	while (i < max)
	{
		if (fabsl(z.imaginary) < 0.01L && fmodl(fabsl(z.real), M_PI) < 0.01L)
			return (i + (int) (fabsl(z.real) / M_PI) * 10);
		poly = newton_poly_div_hourglass(z);
		z.real = z.real - poly.real;
		z.imaginary = z.imaginary - poly.imaginary;
		i++;
	}
	if (!i)
		return (MAX_ITERATIONS);
	return (i);
}
