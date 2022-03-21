/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/21 17:17:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Handles events for key presses.
*/
int	events_key(int keycode, t_app *app)
{
	ft_printf("keycode: %i, app: %p\n", keycode, app);
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_H)
		app->conf->toggle_help = ft_toggle(app->conf->toggle_help);
	app_render(app);
	return (0);
}

/*
 * Handles events for mouse..
*/
int	events_mouse(int mousecode, int x, int y, t_app *app)
{
	ft_printf("mousecode: %i x: %i y: %i app: %p\n", mousecode, x, y, app);
	app_render(app);
	return (0);
}

/*
 * Handles continuous events.
*/
int	events_loop(t_app *app)
{
	if (!app->conf->animation)
		return (0);
	app_render(app);
	return (0);
}
