/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/18 14:25:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	init_app(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	if (!(*app))
		return (0);
	return (1);
}

void	run_app(t_app **app)
{
	(*app)->mlx = mlx_init();
	(*app)->win = mlx_new_window((*app)->mlx, (*app)->conf->win_w,
		(*app)->conf->win_h, (*app)->conf->win_name);
	mlx_key_hook((*app)->win, events_key, app);
	mlx_mouse_hook((*app)->win, events_mouse, app);
	mlx_loop_hook((*app)->mlx, events_loop, app);
	mlx_loop((*app)->mlx);
}
