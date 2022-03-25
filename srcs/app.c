/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 10:58:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Calculates FPS and displays it.
*/
static void	update_fps_counter(t_app *app)
{
	int	time_since;

	app->conf->fps_count++;
	if (time(NULL) > app->conf->fps_time + 2)
	{
		time_since = time(NULL) - app->conf->fps_time;
		app->conf->fps = app->conf->fps_count / time_since;
		app->conf->fps_time = time(NULL);
		app->conf->fps_count = 0;
	}
	mlx_string_put(app->mlx, app->win, 170, 0, 0xFFFFFF, "FPS");
	mlx_string_put(app->mlx, app->win, 210, 0, 0xFFFFFF,
		ft_itoa(app->conf->fps));
}

static void	display_help(t_app *app)
{
	int					i;
	int					x;
	int					y;
	static const char	*h[] = {
		"[1]                   FRACTAL: Mandelbrot set",
		"[2]                   FRACTAL: Julia set",
		"[h]                   Toggle help",
		"[a]                   Toggle animation",
		"[c]                   Toggle chaos",
		"[m]                   Toggle mouse tracking (Julia)",
		"[esc]                 Exit",
		NULL,
	};

	i = 0;
	x = app->conf->win_w / 2 - 200;
	y = app->conf->win_h / 2 - 140;
	mlx_clear_window(app->mlx, app->win);
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
	mlx_key_hook(app->win, events_keyup, app);
	mlx_hook(app->win, 2, 0, events_keydown, app);
	mlx_hook(app->win, 6, 0, events_mouse_track, app);
	mlx_mouse_hook(app->win, events_mouse, app);
	mlx_loop_hook(app->mlx, events_loop, app);

	app->image = init_image(app->mlx, app->conf);
	if (!app->image)
		exit_error(NULL);
	app_render(app);
	mlx_loop(app->mlx);
}

void	app_render(t_app *app)
{
	flush_image(app->image);
	if (app->conf->toggle_help)
	{
		display_help(app);
		return ;
	}
	fractal_render(app);
	mlx_string_put(app->mlx, app->win, 0, 0, 0xFFFFFF, "[h] Toggle help");
	mlx_string_put(app->mlx, app->win, 260, 0, 0xFFFFFF, "Iterations:");
	mlx_string_put(app->mlx, app->win, 380, 0, 0xFFFFFF, ft_itoa(app->conf->iterations));
	update_fps_counter(app);
}
