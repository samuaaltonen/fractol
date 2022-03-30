/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex_square.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:35:50 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 10:37:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Squares a complex number.
*/
t_complex	ft_complex_square(t_complex a)
{
	t_complex	result;

	result.real = a.real * a.real - a.imaginary * a.imaginary;
	result.imaginary = a.real * a.imaginary + a.imaginary * a.real;
	return (result);
}
