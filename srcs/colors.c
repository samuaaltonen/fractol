/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:50 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/31 15:36:56 by saaltone         ###   ########.fr       */
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
	(void)app;
}