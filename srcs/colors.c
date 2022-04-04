/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:50 by saaltone          #+#    #+#             */
/*   Updated: 2022/04/04 15:48:22 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_color_preset(t_app *app)
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

/*
 * Renders color picker to right-top corner.
*/
void	rgbpicker_render(t_app *app)
{
	int	r;
	int	g;
	int	b;
	int	x;
	int	y;

	x = -1;
	while (++x < 255)
	{
		r = (sin(0.0247 * x + 2) + 1) * 127;
		g = (sin(0.0247 * x) + 1) * 127;
		b = (sin(0.0247 * x + 4) + 1) * 127;
		y = -1;
		while (++y < 255)
		{
			if (--r < 0)
				r = 0;
			if (--g < 0)
				g = 0;
			if (--b < 0)
				b = 0;
			put_pixel_to_image(app->image, WIN_W - x, y, ft_rgbtoint(r, g, b));
		}
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}