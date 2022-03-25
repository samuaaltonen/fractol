/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:21:47 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/25 16:07:08 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_app	*app;

	if (!app_init(&app) || !conf_init(app))
		exit_error(NULL);
	if (ac != 2)
	{
		print_usage();
		exit(EXIT_SUCCESS);
	}
	parse_input(app, av[1]);
	app_run(app);
	return (0);
}
