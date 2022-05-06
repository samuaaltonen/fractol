/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:11:38 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/06 15:53:48 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static char	**gallery_read_snapshots(void)
{
	int		i;
	int		fd;
	char	**snapshots;
	char	*line;

	snapshots = (char **)malloc(sizeof(char *) * (MAX_SNAPSHOT_ROWS * MAX_SNAPSHOT_COLS + 1));
	if (!snapshots)
		exit_error(MSG_ERROR_ALLOC);
	ft_bzero(snapshots, sizeof(char *) * MAX_SNAPSHOT_ROWS * MAX_SNAPSHOT_COLS + 1);
	fd = open(SNAPSHOT_FILE, O_RDONLY);
	if (fd < 0)
		exit_error(MSG_ERROR_SNAPSHOT_FILE);
	i = 0;
	while (i < MAX_SNAPSHOT_ROWS * MAX_SNAPSHOT_COLS && ft_get_next_line(fd, &(snapshots[i])) > 0)
		i++;
	while(ft_get_next_line(fd, &line))
		free(line);
	close(fd);
	return (snapshots);
}

static void	gallery_background(t_app *app)
{
	flush_image(app->image);
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}

void	gallery_display(t_app *app)
{
	int		row;
	int		col;
	char	**snapshots;

	gallery_background(app);
	snapshots = gallery_read_snapshots();
	replace_image_new(app, WIN_W / MAX_SNAPSHOT_COLS, WIN_H / MAX_SNAPSHOT_ROWS);
	row = 0;
	while (row < MAX_SNAPSHOT_ROWS)
	{
		col = 0;
		while (col < MAX_SNAPSHOT_COLS && snapshots[row * MAX_SNAPSHOT_COLS + col])
		{
			gallery_load_snapshot(app, snapshots[row * MAX_SNAPSHOT_COLS + col]);
			fractal_render_singlethread(app);
			mlx_put_image_to_window(app->mlx, app->win, app->image->img, col * WIN_W / MAX_SNAPSHOT_COLS, row * WIN_H / MAX_SNAPSHOT_ROWS);
			col++;
		}
		row++;
	}
	free(snapshots);
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
	replace_image_new(app, WIN_W, WIN_H);
}
