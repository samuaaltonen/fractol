/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 15:41:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Changes fractal set.
*/
static void	change_fractal(int keycode, t_app *app)
{
	if (keycode == KEY_1)
	{
		app->conf->fractal_id = FRACTAL_MANDELBROT;
		app->conf->fractal_iterator = fractal_iterate_mandelbrot;
	}
	if (keycode == KEY_2)
	{
		app->conf->fractal_id = FRACTAL_JULIA;
		app->conf->fractal_iterator = fractal_iterate_julia;
	}
	init_fractal_coordinates(app);
}

/*
 * Handles events for key presses (keyup).
*/
int	events_keyup(int keycode, t_app *app)
{
	ft_printf("keycode: %i, app: %p\n", keycode, app);
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_H)
		app->conf->toggle_help = ft_toggle(app->conf->toggle_help);
	if (keycode == KEY_A)
		app->conf->toggle_animation = ft_toggle(app->conf->toggle_animation);
	if (keycode == KEY_C)
	{
		app->conf->toggle_chaos = ft_toggle(app->conf->toggle_chaos);
		if (app->conf->toggle_chaos)
			app->conf->colors = app->conf->chaos_preset;
		else
			app->conf->colors = app->conf->color_preset;
	}
	if (keycode == KEY_M)
		app->conf->toggle_tracking = ft_toggle(app->conf->toggle_tracking);
	if (keycode == KEY_1 || keycode == KEY_2 || keycode == KEY_3
		|| keycode == KEY_4 || keycode == KEY_5 || keycode == KEY_6)
		change_fractal(keycode, app);
	app_render(app);
	return (0);
}

/*
 * Handles events for key presses (keydown).
*/
int	events_keydown(int keycode, t_app *app)
{
	if (keycode == KEY_PGDOWN)
		app->conf->iterations -= 1;
	if (keycode == KEY_PGUP)
		app->conf->iterations += 1;
	if (app->conf->iterations < 0)
		app->conf->iterations = 0;
	if (app->conf->iterations > MAX_ITERATIONS)
		app->conf->iterations = MAX_ITERATIONS;
	if (keycode == KEY_ARROW_UP)
		app->conf->grid.y -= 0.03125 * app->conf->grid.y_w;
	if (keycode == KEY_ARROW_DOWN)
		app->conf->grid.y += 0.03125 * app->conf->grid.y_w;
	if (keycode == KEY_ARROW_LEFT)
		app->conf->grid.x -= 0.03125 * app->conf->grid.x_w;
	if (keycode == KEY_ARROW_RIGHT)
		app->conf->grid.x += 0.03125 * app->conf->grid.x_w;
	app_render(app);
	return (0);
}
