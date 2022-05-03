/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gallery_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:11:38 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/03 14:26:08 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	gallery_display(t_app *app)
{
	flush_image(app->image);
	mlx_put_image_to_window(app->mlx, app->win, app->image->img, 0, 0);
}
