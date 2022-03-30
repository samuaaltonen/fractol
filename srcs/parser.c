/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:59:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 10:25:45 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Changes fractal set.
*/
void	switch_fractal(t_app *app)
{
	if (app->conf->fractal_id == FRACTAL_MANDELBROT)
	{
		app->conf->fractal_iterator = fractal_iterate_mandelbrot;
		app->conf->grid = (t_grid){-2.L, -1.L, 3.L, 2.L};
	}
	if (app->conf->fractal_id == FRACTAL_JULIA)
	{
		app->conf->fractal_iterator = fractal_iterate_julia;
		app->conf->grid = (t_grid){-2.L, -2.L, 4.L, 4.L};
	}
	if (app->conf->fractal_id == FRACTAL_BURNING_SHIP)
	{
		app->conf->iterations = 30;
		app->conf->fractal_iterator = fractal_iterate_burning_ship;
		app->conf->grid = (t_grid){-2.L, -1.5L, 3.L, 2.L};
	}
	if (app->conf->fractal_id == FRACTAL_NEWTON)
	{
		app->conf->iterations = 30;
		app->conf->fractal_iterator = fractal_iterate_newton_poly_1;
		app->conf->grid = (t_grid){-4.L, -2.L, 8.L, 4.L};
	}
}

/*
 * Parses fractal id from application arguments and switches to it.
*/
void	parse_input(t_app *app, char *number)
{
	int	fractal_id;

	fractal_id = ft_atoi(number);
	if (fractal_id < 1 || fractal_id > 6)
	{
		print_usage();
		exit(EXIT_SUCCESS);
	}
	app->conf->fractal_id = fractal_id;
	switch_fractal(app);
}