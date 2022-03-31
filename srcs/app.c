/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/31 12:56:24 by saaltone         ###   ########.fr       */
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
}

static void	display_help(t_app *app)
{
	int					i;
	static const char	*h[] = {
		"[1]               FRACTAL: Mandelbrot set",
		"[2]               FRACTAL: Julia set",
		"[3]               FRACTAL: Burning ship",
		"[4]               FRACTAL: Newton Chains",
		"[5]               FRACTAL: Hourglass",
		"[h]               Toggle help",
		"[a]               Toggle animation",
		"[c]               Toggle chaos",
		"[m]               Toggle mouse tracking (Julia)",
		"[r]               Toggle rendering (On by default)",
		"[q]               Decrease thread count",
		"[w]               Increase thread count",
		"[esc]             Exit",
		NULL,
	};

	mlx_clear_window(app->mlx, app->win);
	mlx_string_put(app->mlx, app->win, app->conf->win_w / 2 - 330,
		app->conf->win_h / 2 - 140, 16777215, "Controls:");
	i = -1;
	while (h[++i])
		mlx_string_put(app->mlx, app->win, app->conf->win_w / 2 - 200,
			app->conf->win_h / 2 - 140 + i * 30, 3471870, (char *) h[i]);
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
	char	*temp;

	if (app->conf->toggle_help)
	{
		flush_image(app->image);
		display_help(app);
		return ;
	}
	fractal_render_multithreaded(app);
	update_fps_counter(app);
	mlx_string_put(app->mlx, app->win, 0, 0, 0xFFFFFF, "[h] Toggle help");
	mlx_string_put(app->mlx, app->win, 0, 20, 0xFFFFFF, "Iterations:");
	temp = ft_itoa(app->conf->iterations);
	mlx_string_put(app->mlx, app->win, 120, 20, 0xFFFFFF, temp);
	free(temp);
	temp = ft_itoa(app->conf->thread_count);
	mlx_string_put(app->mlx, app->win, 0, 40, 0xFFFFFF, "Threads:");
	mlx_string_put(app->mlx, app->win, 120, 40, 0xFFFFFF, temp);
	free(temp);
	temp = ft_itoa(app->conf->fps);
	mlx_string_put(app->mlx, app->win, 0, 60, 0xFFFFFF, "FPS:");
	mlx_string_put(app->mlx, app->win, 120, 60, 0xFFFFFF, temp);
	free(temp);
}
