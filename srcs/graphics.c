/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 18:10:24 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*fractal_render(void *data)
{
	t_thread_data	*t;
	t_app			*app;
	int				x;
	int				y;
	int				result;

	t = (t_thread_data *)data;
	app = (t_app *)t->app;
	x = t->x_start - 1;
	while (++x < t->x_end)
	{
		y = t->y_start - 1;
		while (++y < t->y_end)
		{
			result = app->conf->fractal_iterator((t_complex){
					x * app->conf->grid.x_w / WIN_W + app->conf->grid.x,
					y * app->conf->grid.y_w / WIN_H + app->conf->grid.y},
					app->conf->c, app->conf->iterations);
			if (result < app->conf->iterations)
				put_pixel_to_image(app->image, x, y,
					app->conf->colors[app->conf->color_step + result]);
			else
				put_pixel_to_image(app->image, x, y, 0);
		}
	}
	pthread_exit(NULL);
}

/*
 * Divides fractal rendering work to different threads.
*/
void	fractal_render_multithreaded(t_app *app)
{
	int			id;
	pthread_t	thread_identifiers[THREADS_MAX];

	id = 0;
	while (id < app->conf->thread_count)
	{
		if (pthread_create(&thread_identifiers[id], NULL, fractal_render,
				(void *)(&(app->thread_info)[id])))
			exit_error(MSG_ERROR_THREADS);
		id++;
	}
	id = 0;
	while (id < app->conf->thread_count)
	{
		pthread_join(thread_identifiers[id], NULL);
		id++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}


