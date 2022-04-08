/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:20:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/04/07 13:00:37 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_NAME "Fractol"
# define WIN_W 1280
# define WIN_H 720
# define DEFAULT_ITERATIONS 80
# define MAX_ITERATIONS 300
# define COLOR_COUNT 80
# define MSG_USAGE "{cyan}Usage: {reset}./fractol [fractal_id]\n\
{cyan}Possible fractals:{reset}\n\
  1: Mandelbrot\n\
  2: Julia\n\
  3: Burning Ship\n\
  4: Newton Chains\n\
  5: Blackhole\n"
# define MSG_ERROR "Error occured"
# define MSG_ERROR_IMAGE_INIT "Image initialization failed."
# define MSG_ERROR_THREADS "Could not create thread for fractal rendering."
# define MSG_ERROR_SNAPSHOT_FILE "Could not open/create snapshot file."
# define MSG_ERROR_SNAPSHOT_WRITE "Could not write to snapshot file."
# define FRACTAL_MANDELBROT 1
# define FRACTAL_JULIA 2
# define FRACTAL_BURNING_SHIP 3
# define FRACTAL_NEWTON 4
# define FRACTAL_BLACKHOLE 5
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_H 4
# define KEY_X 7
# define KEY_C 8
# define KEY_Q 12
# define KEY_W 13
# define KEY_R 15
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
# define MOUSE_CLICK_LEFT 1
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define THREADS_DEFAULT 8
# define THREADS_MAX 32
# define SNAPSHOT_FILE "snapshots.txt"
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

typedef struct s_grid
{
	long double	x;
	long double	y;
	long double	x_w;
	long double	y_w;
}	t_grid;

typedef struct s_thread_data
{
	void	*app;
	int		x_start;
	int		y_start;
	int		x_end;
	int		y_end;
}	t_thread_data;

typedef struct s_complex
{
	long double	real;
	long double	imaginary;
}	t_complex;

typedef struct s_conf
{
	char		*win_name;
	int			win_w;
	int			win_h;
	int			toggle_help;
	int			toggle_rgbpicker;
	int			toggle_animation;
	int			toggle_chaos;
	int			toggle_tracking;
	int			toggle_rendering;
	int			fractal_id;
	int			(*fractal_iterator)(t_complex, t_complex, int);
	int			iterations;
	int			color_step;
	int			selected_color;
	int			color_preset[COLOR_COUNT + MAX_ITERATIONS];
	int			chaos_preset[COLOR_COUNT + MAX_ITERATIONS];
	int			*colors;
	int			fps;
	int			fps_time;
	int			fps_count;
	int			total_iterations;
	int			thread_count;
	t_grid		grid;
	t_complex	c;
}	t_conf;

typedef struct s_app
{
	t_conf			*conf;
	t_image			*image;
	void			*mlx;
	void			*win;
	t_thread_data	thread_info[THREADS_MAX];
}	t_app;

/*
 * Messages
*/
void	print_usage(void);
void	exit_error(char *message);

/*
 * Configuration
*/
int		conf_init(t_app *app);
void	init_thread_info(t_app *app);

/*
 * Input
*/
void	parse_input(t_app *app, char *number);

/*
 * Colors
*/
void	init_color_preset(t_app *app);
void	rgbpicker_render(t_app *app);
void	rgbpicker_slot_select(t_app *app, int x, int y);
void	rgbpicker_slot_set(t_app *app, int x, int y);
void	rgbpicker_init_gradients(t_app *app, int index_start, int index_end);

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
int		get_pixel_color(t_image *image, int x, int y);
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
void	switch_fractal(t_app *app);
int		fractal_iterate_mandelbrot(t_complex z, t_complex c, int max);
int		fractal_iterate_julia(t_complex z, t_complex c, int max);
int		fractal_iterate_burning_ship(t_complex z, t_complex c, int max);
int		fractal_iterate_newton_chains(t_complex z, t_complex c, int max);
int		fractal_iterate_newton_blackhole(t_complex z, t_complex c, int max);

/*
 * Graphics
*/
void	fractal_render_multithreaded(t_app *app);

/*
 * Gallery
*/
void	gallery_save_snapshot(t_app *app);

#endif
