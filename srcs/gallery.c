/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:50:44 by saaltone          #+#    #+#             */
/*   Updated: 2022/04/08 12:09:24 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Saves snapshot of current state. Snapshot consist of: 
 * fractal_id, iteration count, thread count, grid dimensions, colors
*/
void	gallery_save_snapshot(t_app *app)
{
	int		fd;

	fd = open(SNAPSHOT_FILE, O_WRONLY | O_APPEND | O_CREAT, 0755);
	if (fd < 0)
		exit_error(MSG_ERROR_SNAPSHOT_FILE);
	ft_printf_fd(fd, "%i;%i;%i;%Lf %Lf %Lf %Lf;%i %i %i %i %i\n",
		app->conf->fractal_id,
		app->conf->iterations,
		app->conf->thread_count,
		app->conf->grid.x, app->conf->grid.y,
		app->conf->grid.x_w, app->conf->grid.y_w,
		app->conf->colors[0],
		app->conf->colors[COLOR_COUNT / 5],
		app->conf->colors[COLOR_COUNT / 5 * 2],
		app->conf->colors[COLOR_COUNT / 5 * 3],
		app->conf->colors[COLOR_COUNT / 5 * 4]
	);
	close(fd);
}
