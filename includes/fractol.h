/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:20:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/16 15:24:25 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_FRACTOL
# define F_FRACTOL
# define WIN_NAME "Fractol"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MSG_ERROR_IMAGE_INIT "Image initialization failed."
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
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
}	t_conf;

typedef struct s_app
{
	t_conf		*conf;
	t_image		*image;
	void		*mlx;
	void		*win;
}	t_app;

/*
 * Messages
*/
void	print_usage(void);
void	exit_error(char *message);

/*
 * Configuration
*/
int		init_conf(t_app **app);

/*
 * Application
*/
int		init_app(t_app **app);
void	run_app(t_app **app);

#endif
