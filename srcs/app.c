/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/18 15:29:51 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Creates empty image and draws it to the window.
*/
static void	flush_window(t_app *app)
{
	char	*img;

	img = mlx_new_image(app->mlx, app->conf->win_w, app->conf->win_h);
	mlx_put_image_to_window(app->mlx, app->win, img, 0, 0);
	mlx_destroy_image(app->mlx, img);
}

static void	display_help(t_app *app)
{
	int					i;
	int					x;
	int					y;
	static const char	*h[] = {
		"[h]                   Toggle help",
		"[esc]                 Exit",
		NULL,
	};

	i = 0;
	x = app->conf->win_w / 2 - 200;
	y = app->conf->win_h / 2 - 140;
	mlx_string_put(app->mlx, app->win, x - 130, y, 16777215, "Controls:");
	while (h[i])
	{
		mlx_string_put(app->mlx, app->win, x, y + i * 30, 3471870,
			(char *) h[i]);
		i++;
	}
}

int	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	if (!(*app))
		return (0);
	return (1);
}

void	app_run(t_app *app)
{
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, app->conf->win_w,
			app->conf->win_h, app->conf->win_name);
	mlx_key_hook(app->win, events_key, app);
	mlx_mouse_hook(app->win, events_mouse, app);
	mlx_loop_hook(app->mlx, events_loop, app);
	app_render(app);
	mlx_loop(app->mlx);
}

void	app_render(t_app *app)
{
	flush_window(app);
	if (app->conf->toggle_help)
		display_help(app);
	else
		mlx_string_put(app->mlx, app->win, 0, 0,
			3471870, "[h] Toggle help");
}
