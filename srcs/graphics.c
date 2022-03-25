/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 15:28:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*fractal_render(void *data)
{
	t_thread_data	*t;
	int				x;
	int				y;
	int				result;

	t = (t_thread_data *)data;
	x = t->x_start - 1;
	while (++x < t->x_end)
	{
		y = t->y_start - 1;
		while (++y < t->y_end)
		{
			result = t->app->conf->fractal_iterator((t_complex){
					x * t->app->conf->grid.x_w / WIN_W + t->app->conf->grid.x,
					y * t->app->conf->grid.y_w / WIN_H + t->app->conf->grid.y},
					t->app->conf->c, t->app->conf->iterations);
			if (result < t->app->conf->iterations)
				put_pixel_to_image(t->app->image, x, y,
					t->app->conf->colors[t->app->conf->color_step + result]);
			else
				put_pixel_to_image(t->app->image, x, y, 0);
		}
	}
	pthread_exit(NULL);
}

/*
 * Divides fractal rendering work to 4 threads.
*/
void	fractal_render_multithreaded(t_app *app)
{
	int					id;
	pthread_t			thread_identifiers[4];
	const t_thread_data	thread_data[4] = {
	{app, 0, 0, WIN_W / 2, WIN_H / 2},
	{app, WIN_W / 2, 0, WIN_W, WIN_H / 2},
	{app, 0, WIN_H / 2, WIN_W / 2, WIN_H},
	{app, WIN_W / 2, WIN_H / 2, WIN_W, WIN_H},
	};

	id = 0;
	while (id < 4)
	{
		if (pthread_create(&thread_identifiers[id], NULL, fractal_render,
				(void *)(&thread_data[id])))
			exit_error(MSG_ERROR_THREADS);
		id++;
	}
	id = 0;
	while (id < 4)
	{
		pthread_join(thread_identifiers[id], NULL);
		id++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}
