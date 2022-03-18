/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:47 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/18 15:29:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_app	*app;

	(void)av;
	if (ac != 1)
	{
		print_usage();
		exit(EXIT_SUCCESS);
	}
	if (!app_init(&app) || !conf_init(app))
		exit_error(NULL);
	app_run(app);
	return (0);
}
