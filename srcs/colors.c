/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:50 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/12 12:51:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_color_preset(t_app *app)
{
	int		color;
	int		i;
	int		random;
	double	wave_step;

	i = 0;
	wave_step = (2 * M_PI) / COLOR_COUNT;
	srand(time(NULL));
	while (i < COLOR_COUNT + MAX_ITERATIONS)
	{
		color = (int)((sin(wave_step * i + 2) + 1) * 127) << 16;
		color += (int)((sin(wave_step * i) + 1) * 127) << 8;
		color += (int)((sin(wave_step * i + 4) + 1) * 127);
		app->conf->color_preset[i] = color;
		random = rand();
		srand(random);
		random = random % (COLOR_COUNT + MAX_ITERATIONS);
		color = (int)((sin(wave_step * random + 2) + 1) * 127) << 16;
		color += (int)((sin(wave_step * random) + 1) * 127) << 8;
		color += (int)((sin(wave_step * random + 4) + 1) * 127);
		app->conf->chaos_preset[i] = color;
		i++;
	}
	app->conf->colors = app->conf->color_preset;
}

static void	display_selected_colors(t_app *app)
{
	int	x;
	int	y;
	int	color_index;

	x = -1;
	color_index = 0;
	while (++x < 255)
	{
		if (x < 255)
			color_index = COLOR_COUNT / 5 * 4;
		if (x < 204)
			color_index = COLOR_COUNT / 5 * 3;
		if (x < 153)
			color_index = COLOR_COUNT / 5 * 2;
		if (x < 102)
			color_index = COLOR_COUNT / 5;
		if (x < 51)
			color_index = 0;
		y = -1;
		while (++y < 42)
		{
			put_pixel_to_image(app->image, WIN_W - 255 + x, 255 + y,
				app->conf->colors[app->conf->color_step + color_index]);
		}
	}
}

static void	display_color_wave_square(t_app *app)
{
	int	r;
	int	g;
	int	b;
	int	x;
	int	y;

	x = 0;
	while (++x <= 255)
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
}

void	rgbpicker_init_gradients(t_app *app, int index_start, int index_end)
{
	int	i;
	int	len;

	len = index_end - index_start;
	if (len <= 0)
		return ;
	i = 0;
	while (i < len)
	{
		app->conf->colors[index_start + i] = ft_color_between(i / (double) len,
				app->conf->colors[index_start], app->conf->colors[index_end]);
		i++;
	}
	i = COLOR_COUNT;
	while (i < COLOR_COUNT + MAX_ITERATIONS)
	{
		app->conf->colors[i] = app->conf->colors[i - COLOR_COUNT];
		i++;
	}
}

/*
 * Renders color picker to right-top corner.
*/
void	rgbpicker_render(t_app *app)
{
	if (!app->conf->toggle_rendering)
		return ;
	display_color_wave_square(app);
	display_selected_colors(app);
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}
