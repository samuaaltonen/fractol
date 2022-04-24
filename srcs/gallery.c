/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:50:44 by saaltone          #+#    #+#             */
/*   Updated: 2022/04/24 15:12:24 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	gallery_load_mouse(t_app *app, char *mouse_data)
{
	char	**mouse;

	mouse = ft_strsplit(mouse_data, ' ');
	app->conf->c.real = atof(mouse[0]);
	app->conf->c.imaginary = atof(mouse[1]);
	ft_free_array((void **)mouse);
}

static void	gallery_load_colors(t_app *app, char *color_data)
{
	char	**colors;

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

	grid = ft_strsplit(grid_data, ' ');
	app->conf->grid.x = atof(grid[0]);
	app->conf->grid.y = atof(grid[1]);
	app->conf->grid.x_w = atof(grid[2]);
	app->conf->grid.y_w = atof(grid[3]);
	ft_free_array((void **)grid);
}

/*
 * Loads a snapshot from snapshots file and sets config accordingly.
*/
void	gallery_load_snapshot(t_app *app, int snapshot_id)
{
	int		i;
	int		fd;
	char	*snapshot;
	char	**split;

	fd = open(SNAPSHOT_FILE, O_RDONLY);
	if (fd < 0)
		exit_error(MSG_ERROR_SNAPSHOT_FILE);
	i = 0;
	while (i < snapshot_id && ft_get_next_line(fd, &snapshot) > 0)
		i++;
	while (ft_get_next_line(fd, &snapshot) > 0);
	close(fd);
	split = ft_strsplit(snapshot, ';');
	app->conf->fractal_id = ft_atoi(split[0]);
	switch_fractal(app);
	app->conf->toggle_tracking = 0;
	app->conf->iterations = ft_atoi(split[1]);
	app->conf->thread_count = ft_atoi(split[2]);
	gallery_load_grid(app, split[3]);
	gallery_load_colors(app, split[4]);
	gallery_load_mouse(app, split[5]);
	ft_free_array((void **)split);
	free(snapshot);
}

/*
 * Saves snapshot of current state. Snapshot consist of: 
 * fractal_id, iteration count, thread count, grid dimensions, colors, mouse pos
*/
void	gallery_save_snapshot(t_app *app)
{
	int		fd;

	fd = open(SNAPSHOT_FILE, O_WRONLY | O_APPEND | O_CREAT, 0755);
	if (fd < 0)
		exit_error(MSG_ERROR_SNAPSHOT_FILE);
	ft_printf_fd(fd,
		"%i;%i;%i;%.30Lf %.30Lf %.30Lf %.30Lf;%i %i %i %i %i;%.30Lf %.30Lf\n",
		app->conf->fractal_id,
		app->conf->iterations,
		app->conf->thread_count,
		app->conf->grid.x, app->conf->grid.y,
		app->conf->grid.x_w, app->conf->grid.y_w,
		app->conf->colors[0],
		app->conf->colors[COLOR_COUNT / 5],
		app->conf->colors[COLOR_COUNT / 5 * 2],
		app->conf->colors[COLOR_COUNT / 5 * 3],
		app->conf->colors[COLOR_COUNT / 5 * 4],
		app->conf->c.real,
		app->conf->c.imaginary
		);
	close(fd);
}
