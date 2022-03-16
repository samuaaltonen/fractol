/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/16 15:23:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	init_conf(t_app **app)
{
	if (!app || !(*app))
		return (0);
	(*app)->conf = (t_conf *)malloc(sizeof(t_conf));
	if (!((*app)->conf))
		return (0);
	(*app)->conf->win_name = WIN_NAME;
	(*app)->conf->toggle_help = 0;
	(*app)->conf->win_w = WIN_WIDTH;
	(*app)->conf->win_h = WIN_HEIGHT;
	return (1);
}
