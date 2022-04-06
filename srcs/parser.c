/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:59:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/04/05 11:42:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	update_fractal_conf(t_app *app, int iteration_count,
	int (*iterator)(t_complex, t_complex, int), t_grid grid)
{
	app->conf->iterations = iteration_count;
	app->conf->fractal_iterator = iterator;
	app->conf->grid = grid;
}

/*
 * Changes fractal set.
*/
void	switch_fractal(t_app *app)
{
	if (app->conf->fractal_id == FRACTAL_MANDELBROT)
		update_fractal_conf(app, DEFAULT_ITERATIONS, fractal_iterate_mandelbrot,
			(t_grid){-2.L, -1.L, 3.L, 2.L});
	if (app->conf->fractal_id == FRACTAL_JULIA)
		update_fractal_conf(app, DEFAULT_ITERATIONS, fractal_iterate_julia,
			(t_grid){-2.L, -2.L, 4.L, 4.L});
	if (app->conf->fractal_id == FRACTAL_BURNING_SHIP)
		update_fractal_conf(app, 30, fractal_iterate_burning_ship,
			(t_grid){-2.L, -1.5L, 3.L, 2.L});
	if (app->conf->fractal_id == FRACTAL_NEWTON)
		update_fractal_conf(app, DEFAULT_ITERATIONS,
			fractal_iterate_newton_chains, (t_grid){-4.L, -2.L, 8.L, 4.L});
	if (app->conf->fractal_id == FRACTAL_BLACKHOLE)
		update_fractal_conf(app, 200, fractal_iterate_newton_blackhole,
			(t_grid){1.5205L, -0.05L, 0.1L, 0.1L});
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
