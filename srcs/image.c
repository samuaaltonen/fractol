/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/06 14:25:55 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Initializes image.
*/
t_image	*init_image(void *mlx, t_conf *conf)
{
	t_image	*image;

	image = (t_image *)malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->width = conf->win_w;
	image->height = conf->win_h;
	image->img = mlx_new_image(mlx, image->width, image->height);
	image->data = mlx_get_data_addr(image->img, &(image->bpp),
			&(image->line_size), &(image->endian));
	return (image);
}

/*
 * Replaces image with new image with specific size.
*/
void	replace_image_new(t_app *app, int width, int height)
{
	mlx_destroy_image(app->mlx, app->image->img);
	free(app->image);
	app->conf->win_w = width;
	app->conf->win_h = height;
	app->image = init_image(app->mlx, app->conf);
	if (!app->image)
		exit_error(NULL);
}

/* 
 * Changes color of specific pixel in image.
 *
 * line_size = one line/row size in BYTES in image
 * For example: 1920 window width, and 4 bytes per pixel (32 bits, this info is 
 * 				stored in bpp = bits per pixel), line_size would be 7680)
 * 
 * Change pixel by given x,y coordinates: 	
 * 		Count the correct position in image string by
 * 			 y * line_size * 4 + x * 4 (or bpp / 8)
 * 
 * To change color, we need to cast pixel pointer to int pointer type
*/
void	put_pixel_to_image(t_image *image, int x, int y, int color)
{
	int		bytes;
	int		pixel_pos;
	char	*pixel;

	bytes = image->bpp / 8;
	pixel_pos = (y * image->line_size) + (x * bytes);
	if (pixel_pos < 0 || x > image->width || y > image->height)
		return ;
	pixel = image->data + pixel_pos;
	*(int *)pixel = color;
}

/*
 * Returns pixel color at given position.
*/
int	get_pixel_color(t_image *image, int x, int y)
{
	int		bytes;
	int		pixel_pos;
	char	*pixel;

	bytes = image->bpp / 8;
	pixel_pos = (y * image->line_size) + (x * bytes);
	if (pixel_pos < 0 || x > image->width || y > image->height)
		return (0);
	pixel = image->data + pixel_pos;
	return (*(int *)pixel);
}

/*
 * Flushes image (sets all pixels to black)
*/
void	flush_image(t_image *image)
{
	ft_bzero(image->data, image->height * image->line_size);
}
