/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/22 13:01:04 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_color_preset(t_app *app)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (i < COLOR_COUNT)
	{
		r = (sin(0.042 * i + 2) + 1) * 127;
		g = (sin(0.042 * i) + 1) * 127;
		b = (sin(0.042 * i + 4) + 1) * 127;
		app->conf->color_preset[i] = ft_rgbtoint(r, g, b);
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
	app->conf->win_w = WIN_WIDTH;
	app->conf->win_h = WIN_HEIGHT;
	app->conf->fractal_id = FRACTAL_MANDELBROT;
	app->conf->max_iterations = MAX_ITERATIONS;
	app->conf->color_step = 0;
	init_color_preset(app);
	return (1);
}
