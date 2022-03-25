/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:40:40 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 15:41:03 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Handles events for mouse..
*/
int	events_mouse(int mousecode, int x, int y, t_app *app)
{
	ft_printf("mousecode: %i x: %i y: %i\n", mousecode, x, y);
	if (mousecode == MOUSE_SCROLL_UP)
	{
		app->conf->grid.x += x * app->conf->grid.x_w * 0.125 / WIN_W;
		app->conf->grid.y += y * app->conf->grid.y_w * 0.125 / WIN_H;
		app->conf->grid.x_w /= 1.125;
		app->conf->grid.y_w /= 1.125;
	}
	if (mousecode == MOUSE_SCROLL_DOWN)
	{
		app->conf->grid.x -= x * app->conf->grid.x_w * 0.125 / WIN_W;
		app->conf->grid.y -= y * app->conf->grid.y_w * 0.125 / WIN_H;
		app->conf->grid.x_w *= 1.125;
		app->conf->grid.y_w *= 1.125;
	}
	return (0);
}

/*
 * Tracks mouse position and sets initial c value depending on mouse
 * coordinates. (This is used in Julia set).
*/
int	events_mouse_track(int x, int y, t_app *app)
{
	if (!app->conf->toggle_tracking)
		return (0);
	app->conf->c = (t_complex){
		x / (long double)(WIN_W * 2),
		y / (long double)(WIN_H * 2)
	};
	return (0);
}
