/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 18:29:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_color_preset(t_app *app)
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	random;

	i = 0;
	srand(time(NULL));
	while (i < COLOR_COUNT + MAX_ITERATIONS)
	{
		r = (sin(0.042 * i + 2) + 1) * 127;
		g = (sin(0.042 * i) + 1) * 127;
		b = (sin(0.042 * i + 4) + 1) * 127;
		app->conf->color_preset[i] = ft_rgbtoint(r, g, b);
		random = rand();
		srand(random);
		random = random % (COLOR_COUNT + MAX_ITERATIONS);
		r = (sin(0.042 * random + 2) + 1) * 127;
		g = (sin(0.042 * random) + 1) * 127;
		b = (sin(0.042 * random + 4) + 1) * 127;
		app->conf->chaos_preset[i] = ft_rgbtoint(r, g, b);
		i++;
	}
	app->conf->colors = app->conf->color_preset;
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
	app->conf->toggle_animation = 0;
	app->conf->toggle_chaos = 0;
	app->conf->toggle_tracking = 1;
	app->conf->win_w = WIN_W;
	app->conf->win_h = WIN_H;
	app->conf->fractal_id = FRACTAL_MANDELBROT;
	app->conf->fractal_iterator = fractal_iterate_mandelbrot;
	app->conf->iterations = DEFAULT_ITERATIONS;
	app->conf->color_step = 0;
	app->conf->fps_count = 0;
	app->conf->fps = 0;
	app->conf->fps_time = time(NULL);
	app->conf->fps_count = 0;
	app->conf->grid = (t_grid){-2.L, -1.L, 3.L, 2.L};
	app->conf->total_iterations = 0;
	app->conf->c = (t_complex){0.L, 0.L};
	app->conf->thread_count = THREADS_DEFAULT;
	init_color_preset(app);
	init_thread_info(app);
	return (1);
}
