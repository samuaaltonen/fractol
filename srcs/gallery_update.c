/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:02:50 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/12 13:56:24 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		"%i;%i;%i;%.30Lf %.30Lf %.30Lf %.30Lf;%i %i %i %i %i;%i;%.30Lf %.30Lf",
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
		app->conf->color_step,
		app->conf->c.real,
		app->conf->c.imaginary
		);
	ft_printf_fd(fd, "\n");
	close(fd);
}

/*
 * Deletes snapshot by id.
*/
void	gallery_delete_snapshot(int snapshot_id)
{
	int		i;
	int		fd;
	char	**snapshots;

	snapshots = gallery_read_snapshots();
	if (!snapshots)
		return ;
	fd = open(SNAPSHOT_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
		exit_error(MSG_ERROR_SNAPSHOT_FILE);
	i = 0;
	while (i < GALLERY_SLOTS && snapshots[i])
	{
		if (snapshot_id != i)
			ft_printf_fd(fd, "%s\n", snapshots[i]);
		i++;
	}
	ft_free_array((void **)snapshots);
}
