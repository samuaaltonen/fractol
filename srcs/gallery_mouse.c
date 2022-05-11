/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:19:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/11 16:00:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Checks if user pressed delete button. (Top right 10% corner of the snapshot)
*/
static int	gallery_mouse_isdel(int col, int row, int x, int y)
{
	int	col_w;
	int	col_h;

	col_w = WIN_W / GALLERY_COLS;
	col_h = WIN_H / GALLERY_ROWS;
	if (x > col * col_w + col_w / 10 * 9
		&& x < (col + 1) * col_w
		&& y > row * col_h
		&& y < row * col_h + col_h / 10)
		return (1);
	return (0);
}

/*
 * Returns snapshot id which matches the given coordinate (or -1 if no match).
*/
static int	gallery_get_snapshot_id_by_coord(int x, int y)
{
	int		row;
	int		col;
	int		snapshot_id;

	row = -1;
	snapshot_id = -1;
	while (++row < GALLERY_ROWS)
	{
		col = -1;
		while (++col < GALLERY_COLS)
		{
			if (x >= col * WIN_W / GALLERY_COLS
				&& y >= row * WIN_H / GALLERY_ROWS)
			{
				snapshot_id = row * GALLERY_COLS + col;
				if (gallery_mouse_isdel(col, row, x, y))
				{
					gallery_delete_snapshot(snapshot_id);
					return (-1);
				}
			}
		}
	}
	return (snapshot_id);
}

/*
 * Handles mouse events within gallery window.
*/
void	gallery_mouse(t_app *app, int x, int y)
{
	int		snapshot_id;
	char	*snapshot;

	snapshot_id = gallery_get_snapshot_id_by_coord(x, y);
	if (snapshot_id == -1)
		return ;
	snapshot = gallery_read_snapshot(snapshot_id);
	if (snapshot)
	{
		gallery_load_snapshot(app, snapshot);
		app->conf->toggle_gallery = 0;
	}
}
