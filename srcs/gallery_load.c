/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:50:44 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/11 16:03:10 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	gallery_load_mouse(t_app *app, char *mouse_data)
{
	char	**mouse;

	if (ft_strchr_count(mouse_data, ' ') != 1)
		return ;
	mouse = ft_strsplit(mouse_data, ' ');
	app->conf->c.real = atof(mouse[0]);
	app->conf->c.imaginary = atof(mouse[1]);
	ft_free_array((void **)mouse);
}

static void	gallery_load_colors(t_app *app, char *color_data)
{
	char	**colors;

	if (ft_strchr_count(color_data, ' ') != 4)
		return ;
	colors = ft_strsplit(color_data, ' ');
	app->conf->colors[0] = ft_atoi(colors[0]);
	app->conf->colors[COLOR_COUNT / 5] = ft_atoi(colors[1]);
	app->conf->colors[COLOR_COUNT / 5 * 2] = ft_atoi(colors[2]);
	app->conf->colors[COLOR_COUNT / 5 * 3] = ft_atoi(colors[3]);
	app->conf->colors[COLOR_COUNT / 5 * 4] = ft_atoi(colors[4]);
	rgbpicker_init_gradients(app, 0, COLOR_COUNT / 5);
	rgbpicker_init_gradients(app, COLOR_COUNT / 5, COLOR_COUNT / 5 * 2);
	rgbpicker_init_gradients(app, COLOR_COUNT / 5 * 2, COLOR_COUNT / 5 * 3);
	rgbpicker_init_gradients(app, COLOR_COUNT / 5 * 3, COLOR_COUNT / 5 * 4);
	rgbpicker_init_gradients(app, COLOR_COUNT / 5 * 4, COLOR_COUNT);
	ft_free_array((void **)colors);
}

static void	gallery_load_grid(t_app *app, char *grid_data)
{
	char	**grid;

	if (ft_strchr_count(grid_data, ' ') != 3)
		return ;
	grid = ft_strsplit(grid_data, ' ');
	app->conf->grid.x = atof(grid[0]);
	app->conf->grid.y = atof(grid[1]);
	app->conf->grid.x_w = atof(grid[2]);
	app->conf->grid.y_w = atof(grid[3]);
	ft_free_array((void **)grid);
}

/*
 * Loads a snapshot from given snapshot string and sets config accordingly.
*/
void	gallery_load_snapshot(t_app *app, char *snapshot)
{
	char	**split;

	if (!snapshot)
		return ;
	if (ft_strchr_count(snapshot, ';') != 6
		|| ft_strchr_count(snapshot, ' ') != 8)
		return ;
	split = ft_strsplit(snapshot, ';');
	app->conf->fractal_id = ft_atoi(split[0]);
	switch_fractal(app);
	app->conf->toggle_tracking = 0;
	app->conf->iterations = ft_atoi(split[1]);
	app->conf->thread_count = ft_atoi(split[2]);
	gallery_load_grid(app, split[3]);
	gallery_load_colors(app, split[4]);
	app->conf->color_step = ft_atoi(split[5]);
	gallery_load_mouse(app, split[6]);
	ft_free_array((void **)split);
	free(snapshot);
}
