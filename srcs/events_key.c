/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/04/08 14:12:18 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Changes fractal set.
*/
static void	handle_fractal_keys(int keycode, t_app *app)
{
	if (!(keycode == KEY_1 || keycode == KEY_2 || keycode == KEY_3
			|| keycode == KEY_4 || keycode == KEY_5 || keycode == KEY_6))
		return ;
	if (keycode == KEY_1)
		app->conf->fractal_id = FRACTAL_MANDELBROT;
	if (keycode == KEY_2)
		app->conf->fractal_id = FRACTAL_JULIA;
	if (keycode == KEY_3)
		app->conf->fractal_id = FRACTAL_BURNING_SHIP;
	if (keycode == KEY_4)
		app->conf->fractal_id = FRACTAL_NEWTON;
	if (keycode == KEY_5)
		app->conf->fractal_id = FRACTAL_BLACKHOLE;
	switch_fractal(app);
}

/*
 * Changes thread count.
*/
static void	handle_thread_keys(int keycode, t_app *app)
{
	if (!(keycode == KEY_Q || keycode == KEY_W))
		return ;
	if (keycode == KEY_Q)
		app->conf->thread_count--;
	if (keycode == KEY_W)
		app->conf->thread_count++;
	if (app->conf->thread_count < 1)
		app->conf->thread_count = 1;
	if (app->conf->thread_count > THREADS_MAX)
		app->conf->thread_count = THREADS_MAX;
	init_thread_info(app);
}

/*
 * Handles gallery key events, (save snapshot, display snapshots)
*/
static void	handle_gallery_keys(int keycode, t_app *app)
{
	if (keycode == KEY_S)
		gallery_save_snapshot(app);
	if (keycode == KEY_L)
		gallery_load_snapshot(app, 0);
}

/*
 * Handles events for key presses (keyup).
*/
int	events_keyup(int keycode, t_app *app)
{
	ft_printf("%i\n", keycode);
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_H)
		app->conf->toggle_help = ft_toggle(app->conf->toggle_help);
	if (keycode == KEY_C)
		app->conf->toggle_rgbpicker = ft_toggle(app->conf->toggle_rgbpicker);
	if (keycode == KEY_A)
		app->conf->toggle_animation = ft_toggle(app->conf->toggle_animation);
	if (keycode == KEY_X)
	{
		app->conf->toggle_chaos = ft_toggle(app->conf->toggle_chaos);
		if (app->conf->toggle_chaos)
			app->conf->colors = app->conf->chaos_preset;
		else
			app->conf->colors = app->conf->color_preset;
	}
	if (keycode == KEY_M)
		app->conf->toggle_tracking = ft_toggle(app->conf->toggle_tracking);
	if (keycode == KEY_R)
		app->conf->toggle_rendering = ft_toggle(app->conf->toggle_rendering);
	handle_gallery_keys(keycode, app);
	handle_thread_keys(keycode, app);
	handle_fractal_keys(keycode, app);
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
