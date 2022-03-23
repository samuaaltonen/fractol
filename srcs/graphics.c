/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/23 15:13:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*get_fractal_iterator(t_app *app)
{
	static const void	*iterators[] = {
		fractal_iterate_mandelbrot,
		NULL
	};

	return ((void *) iterators[app->conf->fractal_id]);
}

void	fractal_render(t_app *app)
{
	int	x;
	int	y;
	int	(*iterator)(t_complex, int);
	int	result;
	int	*colors;

	colors = app->conf->color_preset;
	if (app->conf->toggle_chaos)
		colors = app->conf->chaos_preset;
	iterator = get_fractal_iterator(app);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			result = (*iterator)((t_complex){
					x * app->conf->grid.x_len / WIN_WIDTH + app->conf->grid.x_min,
					y * app->conf->grid.y_len / WIN_HEIGHT + app->conf->grid.y_min},
					app->conf->max_iterations);
			if (result < app->conf->max_iterations)
				put_pixel_to_image(app->image, x, y,
					colors[app->conf->color_step + result]);
		}
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}
