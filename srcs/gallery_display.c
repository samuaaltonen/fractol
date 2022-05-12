/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:11:38 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/12 13:47:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Reads a single snapshot from snapshot file by id.
*/
char	*gallery_read_snapshot(int snapshot_id)
{
	int		i;
	int		fd;
	char	*snapshot;
	char	*line;

	snapshot = NULL;
	fd = open(SNAPSHOT_FILE, O_RDONLY);
	if (fd < 0)
		exit_error(MSG_ERROR_SNAPSHOT_FILE);
	i = 0;
	while (i < GALLERY_SLOTS && ft_get_next_line(fd, &line) > 0)
	{
		if (i == snapshot_id)
			snapshot = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
	return (snapshot);
}

/*
 * Reads gallery snapshots from a file into array of strings.
*/
char	**gallery_read_snapshots(void)
{
	int		i;
	int		fd;
	char	**snapshots;
	char	*line;

	snapshots = (char **)malloc(sizeof(char *) * (GALLERY_SLOTS + 1));
	if (!snapshots)
		exit_error(MSG_ERROR_ALLOC);
	ft_bzero(snapshots, sizeof(char *) * GALLERY_SLOTS + 1);
	fd = open(SNAPSHOT_FILE, O_RDONLY);
	if (fd < 0)
		exit_error(MSG_ERROR_SNAPSHOT_FILE);
	i = 0;
	while (i < GALLERY_SLOTS && ft_get_next_line(fd, &(snapshots[i])) > 0)
		i++;
	while (ft_get_next_line(fd, &line) > 0)
		free(line);
	close(fd);
	return (snapshots);
}

/*
 * Flushes gallery background (sets all pixels to black).
*/
static void	gallery_background(t_app *app)
{
	flush_image(app->image);
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}

/*
 * Displays delete square
*/
static void	gallery_display_delete_square(t_app *app)
{
	int	col_w;
	int	col_h;
	int	x;
	int	y;

	col_w = WIN_W / GALLERY_COLS;
	col_h = WIN_H / GALLERY_ROWS;
	x = 0;
	while (x < col_w / 10)
	{
		y = 0;
		while (y < col_h / 10)
		{
			put_pixel_to_image(app->image, col_w - x - 1, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

/*
 * Loads all snapshots individually and renders them (with single thread only).
*/
void	gallery_display(t_app *app)
{
	int		row;
	int		col;
	char	**snapshots;

	gallery_background(app);
	snapshots = gallery_read_snapshots();
	replace_image_new(app, WIN_W / GALLERY_COLS, WIN_H / GALLERY_ROWS);
	row = 0;
	while (row < GALLERY_ROWS)
	{
		col = 0;
		while (col < GALLERY_COLS && snapshots[row * GALLERY_COLS + col])
		{
			gallery_load_snapshot(app, snapshots[row * GALLERY_COLS + col]);
			fractal_render_singlethread(app);
			gallery_display_delete_square(app);
			mlx_put_image_to_window(app->mlx, app->win, app->image->img,
				col * WIN_W / GALLERY_COLS,
				row * WIN_H / GALLERY_ROWS);
			col++;
		}
		row++;
	}
	free(snapshots);
	replace_image_new(app, WIN_W, WIN_H);
}
