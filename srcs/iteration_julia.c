/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration_julia.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:33:12 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 12:44:52 by saaltone         ###   ########.fr       */
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
