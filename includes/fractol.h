/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:20:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/22 14:37:53 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_NAME "Fractol"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MAX_ITERATIONS 50
# define COLOR_COUNT 148
# define MSG_USAGE "usage: ./fractol"
# define MSG_ERROR "Error occured"
# define MSG_ERROR_IMAGE_INIT "Image initialization failed."
# define MSG_ERROR_TOO_MANY_ITERATIONS "Iteration count is higher than color \
preset count."
# define FRACTAL_MANDELBROT 0
# define KEY_ESC 53
# define KEY_H 4
# define KEY_A 0
# define KEY_C 8
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <time.h>
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

typedef struct s_conf
{
	char	*win_name;
	int		win_w;
	int		win_h;
	int		toggle_help;
	int		toggle_animation;
	int		toggle_chaos;
	int		fractal_id;
	int		max_iterations;
	int		color_step;
	int		color_preset[COLOR_COUNT + MAX_ITERATIONS];
	int		chaos_preset[COLOR_COUNT + MAX_ITERATIONS];
	int		fps;
	int		fps_time;
	int		fps_count;
}	t_conf;

typedef struct s_app
{
	t_conf		*conf;
	t_image		*image;
	void		*mlx;
	void		*win;
}	t_app;

typedef struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;

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
int		events_key(int keycode, t_app *app);
int		events_mouse(int mousecode, int x, int y, t_app *app);
int		events_loop(t_app *app);

/*
 * Fractal iterators
*/
int		fractal_iterate_mandelbrot(t_complex z);

/*
 * Graphics
*/
void	fractal_render(t_app *app);

#endif
