/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:40:40 by saaltone          #+#    #+#             */
/*   Updated: 2022/04/08 14:11:15 by saaltone         ###   ########.fr       */
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
		app->conf->grid.x_w *= 0.875;
		app->conf->grid.y_w *= 0.875;
	}
	if (mousecode == MOUSE_SCROLL_DOWN)
	{
		app->conf->grid.x -= x * app->conf->grid.x_w * 0.125 / WIN_W;
		app->conf->grid.y -= y * app->conf->grid.y_w * 0.125 / WIN_H;
		app->conf->grid.x_w *= 1.125;
		app->conf->grid.y_w *= 1.125;
	}
	if (mousecode == MOUSE_CLICK_LEFT && app->conf->selected_color == -1)
		rgbpicker_slot_select(app, x, y);
	if (mousecode == MOUSE_CLICK_LEFT && app->conf->selected_color > -1)
		rgbpicker_slot_set(app, x, y);
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

/*
 * Sets color slot as active.
*/
void	rgbpicker_slot_select(t_app *app, int x, int y)
{
	if (x < WIN_W - 255 || y < 255 || x > WIN_W || y > 297)
		return ;
	app->conf->color_step = 0;
	if (x < WIN_W)
		app->conf->selected_color = 4;
	if (x < WIN_W - 51)
		app->conf->selected_color = 3;
	if (x < WIN_W - 102)
		app->conf->selected_color = 2;
	if (x < WIN_W - 153)
		app->conf->selected_color = 1;
	if (x < WIN_W - 204)
		app->conf->selected_color = 0;
}

/*
 * Sets color slot as active.
*/
void	rgbpicker_slot_set(t_app *app, int x, int y)
{
	int	index;
	int	cursor_color;

	if (app->conf->selected_color == -1
		|| x < 0 || y < 0 || x > WIN_W || y > WIN_H)
		return ;
	if (x > WIN_W - 255 && y > 255 && x < WIN_W && y < 297)
		return ;
	cursor_color = get_pixel_color(app->image, x, y);
	index = (COLOR_COUNT / 5) * app->conf->selected_color;
	app->conf->selected_color = -1;
	app->conf->colors[index] = cursor_color;
	rgbpicker_init_gradients(app, index, index + (COLOR_COUNT / 5));
	if (index > 0)
		rgbpicker_init_gradients(app, index - (COLOR_COUNT / 5), index);
}
