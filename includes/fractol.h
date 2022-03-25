/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:20:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 14:44:54 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_NAME "Fractol"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define DEFAULT_ITERATIONS 50
# define MAX_ITERATIONS 300
# define COLOR_COUNT 148
# define MSG_USAGE "usage: ./fractol"
# define MSG_ERROR "Error occured"
# define MSG_ERROR_IMAGE_INIT "Image initialization failed."
# define MSG_ERROR_THREADS "Could not create thread for fractal rendering."
# define FRACTAL_MANDELBROT 0
# define FRACTAL_JULIA 1
# define KEY_ESC 53
# define KEY_H 4
# define KEY_A 0
# define KEY_C 8
# define KEY_M 46
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_ARROW_UP 126
# define KEY_ARROW_DOWN 125
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124
# define KEY_PGUP 116
# define KEY_PGDOWN 121
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <time.h>
# include <pthread.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_image
{
	int		bpp;
	int		line_size;
	int		width;
	int		height;
	int		endian;
	char	*img;
	char	*data;
}	t_image;

typedef struct s_complex
{
	long double	real;
	long double	imaginary;
}	t_complex;

typedef struct s_grid
{
	long double	x_min;
	long double	y_min;
	long double	x_len;
	long double	y_len;
}	t_grid;

typedef struct s_conf
{
	char		*win_name;
	int			win_w;
	int			win_h;
	int			toggle_help;
	int			toggle_animation;
	int			toggle_chaos;
	int			toggle_tracking;
	int			fractal_id;
	int			iterations;
	int			color_step;
	int			color_preset[COLOR_COUNT + MAX_ITERATIONS];
	int			chaos_preset[COLOR_COUNT + MAX_ITERATIONS];
	int			fps;
	int			fps_time;
	int			fps_count;
	int			total_iterations;
	t_grid		grid;
	t_complex	c;
}	t_conf;

typedef struct s_app
{
	t_conf		*conf;
	t_image		*image;
	void		*mlx;
	void		*win;
}	t_app;

typedef struct s_thread_data
{
	t_app	*app;
	int		x_start;
	int		y_start;
	int		x_end;
	int		y_end;
}	t_thread_data;

/*
 * Messages
*/
void	print_usage(void);
void	exit_error(char *message);

/*
 * Configuration
*/
int		conf_init(t_app *app);

/*
 * Application
*/
int		app_init(t_app **app);
void	app_run(t_app *app);
void	app_render(t_app *app);

/*
 * Images
*/
t_image	*init_image(void *mlx, t_conf *conf);
void	put_pixel_to_image(t_image *image, int x, int y, int color);
void	flush_image(t_image *image);

/*
 * Events
*/
int		events_keyup(int keycode, t_app *app);
int		events_keydown(int keycode, t_app *app);
int		events_mouse(int mousecode, int x, int y, t_app *app);
int		events_mouse_track(int x, int y, t_app *app);
int		events_loop(t_app *app);

/*
 * Fractal iterators
*/
void	init_fractal_coordinates(t_app *app);
int		fractal_iterate_mandelbrot(t_complex z, t_complex c, int iterations);
int		fractal_iterate_julia(t_complex z, t_complex c, int iterations);

/*
 * Graphics
*/
void	fractal_render_multithreaded(t_app *app);

#endif
