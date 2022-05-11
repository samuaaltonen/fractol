/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:19:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/11 13:53:21 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Handles mouse events within gallery window.
*/
void	gallery_mouse(t_app *app, int x, int y)
{
	int		row;
	int		col;
	int		snapshot_id;
	char	*snapshot;

	row = -1;
	snapshot_id = -1;
	while (++row < GALLERY_ROWS)
	{
		col = -1;
		while (++col < GALLERY_COLS)
		{
			if (x >= col * WIN_W / GALLERY_COLS
				&& y >= row * WIN_H / GALLERY_ROWS)
				snapshot_id = row * GALLERY_COLS + col;
		}
	}
	if (snapshot_id == -1)
		return ;
	snapshot = gallery_read_snapshot(snapshot_id);
	if (snapshot)
	{
		gallery_load_snapshot(app, snapshot);
		app->conf->toggle_gallery = 0;
	}
}
