/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:18:47 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/21 13:33:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Prints usage.
*/
void	print_usage(void)
{
	ft_putendl(MSG_USAGE);
}

/*
 * Exit the program and print an error message (either with perror or variable)
*/
void	exit_error(char *message)
{
	if (message)
		ft_putendl(message);
	else
		perror(MSG_ERROR);
	exit(EXIT_FAILURE);
}
