/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 11:01:31 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Changes fractal set.
*/
static void	change_fractal(int keycode, t_app *app)
{
	if (keycode == KEY_1)
		app->conf->fractal_id = FRACTAL_MANDELBROT;
	if (keycode == KEY_2)
		app->conf->fractal_id = FRACTAL_JULIA;
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
		app->conf->toggle_chaos = ft_toggle(app->conf->toggle_chaos);
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
	if (keycode == KEY_ARROW_LEFT)
		app->conf->iterations -= 1;
	if (keycode == KEY_ARROW_RIGHT)
		app->conf->iterations += 1;
	if (app->conf->iterations < 0)
		app->conf->iterations = 0;
	if (app->conf->iterations > MAX_ITERATIONS)
		app->conf->iterations = MAX_ITERATIONS;
	app_render(app);
	return (0);
}

/*
 * Handles events for mouse..
*/
int	events_mouse(int mousecode, int x, int y, t_app *app)
{
	ft_printf("mousecode: %i x: %i y: %i\n", mousecode, x, y);
	if (mousecode == MOUSE_SCROLL_UP)
	{
		app->conf->grid.x_min += x * app->conf->grid.x_len * 0.125 / WIN_WIDTH;
		app->conf->grid.y_min += y * app->conf->grid.y_len * 0.125 / WIN_HEIGHT;
		app->conf->grid.x_len /= 1.125;
		app->conf->grid.y_len /= 1.125;
	}
	if (mousecode == MOUSE_SCROLL_DOWN)
	{
		app->conf->grid.x_min -= x * app->conf->grid.x_len * 0.125 / WIN_WIDTH;
		app->conf->grid.y_min -= y * app->conf->grid.y_len * 0.125 / WIN_HEIGHT;
		app->conf->grid.x_len *= 1.125;
		app->conf->grid.y_len *= 1.125;
	}
	return (0);
}

/*
 * Tracks mouse position and sets initial c value depending on mouse
 * coordinates. (This is used in Julia set).
*/
int	events_mouse_track(int x, int y, t_app *app)
{
	if (!app->conf->toggle_tracking)
		return (0);
	app->conf->c = (t_complex){
			x / (long double) (WIN_WIDTH * 2),
			y / (long double) (WIN_HEIGHT * 2)
		};
	return (0);
}

/*
 * Handles continuous events.
*/
int	events_loop(t_app *app)
{
	if (app->conf->toggle_animation)
	{
		app->conf->color_step++;
		if (app->conf->color_step >= COLOR_COUNT)
			app->conf->color_step = 0;
	}
	app_render(app);
	return (0);
}
