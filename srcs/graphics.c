/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/21 17:17:20 by saaltone         ###   ########.fr       */
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
	int			x;
	int			y;
	t_complex	z;
	int			(*iterator)(t_complex);

	iterator = get_fractal_iterator(app);
	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			z.real = (x / (double) WIN_WIDTH) * 3 - 2;
			z.imaginary = (y / (double) WIN_HEIGHT) * 2 - 1;
			if ((*iterator)(z) < MAX_ITERATIONS)
				put_pixel_to_image(app->image, x, y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}
