/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 14:15:12 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*get_fractal_iterator(t_app *app)
{
	static const void	*iterators[] = {
		fractal_iterate_mandelbrot,
		fractal_iterate_julia,
		NULL
	};

	return ((void *) iterators[app->conf->fractal_id]);
}

static void	*fractal_render(void *data)
{
	t_thread_data	*thread;
	int	x;
	int	y;
	int	(*iterator)(t_complex, t_complex, int);
	int	result;
	int	*colors;

	thread = (t_thread_data *)data;
	colors = thread->app->conf->color_preset;
	if (thread->app->conf->toggle_chaos)
		colors = thread->app->conf->chaos_preset;
	iterator = get_fractal_iterator(thread->app);
	x = thread->x_start - 1;
	while (++x < thread->x_end)
	{
		y = thread->y_start - 1;
		while (++y < thread->y_end)
		{
			result = (*iterator)((t_complex){
					x * thread->app->conf->grid.x_len / WIN_WIDTH + thread->app->conf->grid.x_min,
					y * thread->app->conf->grid.y_len / WIN_HEIGHT + thread->app->conf->grid.y_min},
					thread->app->conf->c,
					thread->app->conf->iterations);
			if (result < thread->app->conf->iterations)
				put_pixel_to_image(thread->app->image, x, y,
					colors[thread->app->conf->color_step + result]);
			else
				put_pixel_to_image(thread->app->image, x, y, 0);
		}
	}
	pthread_exit(NULL);
}

void	fractal_render_multithreaded(t_app *app)
{
	int					id;
	pthread_t			thread_identifiers[4];
	const t_thread_data	thread_data[4] = {
		{app, 0, 0, WIN_WIDTH / 2, WIN_HEIGHT / 2},
		{app, WIN_WIDTH / 2, 0, WIN_WIDTH, WIN_HEIGHT / 2},
		{app, 0, WIN_HEIGHT / 2, WIN_WIDTH / 2, WIN_HEIGHT},
		{app, WIN_WIDTH / 2, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT},
	};

	id = 0;
	while (id < 4)
	{
		pthread_create(&thread_identifiers[id], NULL, fractal_render, (void *)(&thread_data[id]));
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
