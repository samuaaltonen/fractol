/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:41:22 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 15:41:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Handles continuous events.
*/
int	events_loop(t_app *app)
{
	if (app->conf->toggle_animation)
	{
		app->conf->color_step++;
		if (app->conf->color_step >= COLOR_COUNT)
			app->conf->color_step = 0;
	}
	app_render(app);
	return (0);
}
