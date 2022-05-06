/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/06 14:04:59 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fracal_conf(t_app *app)
{
	app->conf->fractal_id = FRACTAL_MANDELBROT;
	app->conf->fractal_iterator = fractal_iterate_mandelbrot;
	app->conf->iterations = DEFAULT_ITERATIONS;
	app->conf->color_step = 55;
	app->conf->fps_count = 0;
	app->conf->fps = 0;
	app->conf->fps_time = time(NULL);
	app->conf->fps_count = 0;
	app->conf->grid = (t_grid){-2.L, -1.L, 3.L, 2.L};
	app->conf->total_iterations = 0;
	app->conf->c = (t_complex){0.L, 0.L};
}

void	init_thread_info(t_app *app)
{
	int	i;
	int	width_per_thread;

	i = 0;
	width_per_thread = WIN_W / app->conf->thread_count;
	while (i < app->conf->thread_count && i < THREADS_MAX)
	{
		app->thread_info[i] = (t_thread_data){
			app,
			width_per_thread * i,
			0,
			width_per_thread * (i + 1),
			WIN_H
		};
		i++;
	}
}

int	conf_init(t_app *app)
{
	if (!app)
		return (0);
	app->conf = (t_conf *)malloc(sizeof(t_conf));
	if (!(app->conf))
		return (0);
	app->conf->win_name = WIN_NAME;
	app->conf->toggle_help = 0;
	app->conf->toggle_rgbpicker = 0;
	app->conf->toggle_animation = 0;
	app->conf->toggle_chaos = 0;
	app->conf->toggle_tracking = 1;
	app->conf->toggle_rendering = 1;
	app->conf->toggle_gallery = 0;
	app->conf->win_w = WIN_W;
	app->conf->win_h = WIN_H;
	app->conf->thread_count = THREADS_DEFAULT;
	app->conf->selected_color = -1;
	init_fracal_conf(app);
	init_color_preset(app);
	init_thread_info(app);
	return (1);
}
