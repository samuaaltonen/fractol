/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/22 14:44:22 by saaltone         ###   ########.fr       */
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
	if (keycode == KEY_A)
		app->conf->toggle_animation = ft_toggle(app->conf->toggle_animation);
	if (keycode == KEY_C)
		app->conf->toggle_chaos = ft_toggle(app->conf->toggle_chaos);
	app_render(app);
	return (0);
}

/*
 * Handles events for mouse..
*/
int	events_mouse(int mousecode, int x, int y, t_app *app)
{
	ft_printf("mousecode: %i x: %i y: %i app: %p\n", mousecode, x, y, app);
	if (mousecode == MOUSE_SCROLL_UP)
		app->conf->zoom_multiplier /= 1.05;
	if (mousecode == MOUSE_SCROLL_DOWN)
		app->conf->zoom_multiplier *= 1.05;
	app_render(app);
	return (0);
}

/*
 * Handles continuous events.
*/
int	events_loop(t_app *app)
{
	if (!app->conf->toggle_animation)
		return (0);
	app->conf->color_step++;
	if (app->conf->color_step >= COLOR_COUNT)
		app->conf->color_step = 0;
	app_render(app);
	return (0);
}
