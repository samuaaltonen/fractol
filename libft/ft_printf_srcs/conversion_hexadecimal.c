/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_hexadecimal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:09:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/16 15:34:17 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hex_precision(t_conf **conf, char **output)
{
	int		i;
	int		len;
	char	*zeros;
	char	*joined;

	if ((*conf)->precision < 0)
		return ;
	len = ft_strlen(*output);
	if ((*conf)->precision <= len)
		return ;
	zeros = ft_strnew((*conf)->precision - len);
	if (!zeros)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	i = 0;
	while (i < (*conf)->precision - len)
	{
		zeros[i] = '0';
		i++;
	}
	joined = ft_strjoin(zeros, *output);
	if (!joined)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	free(*output);
	free(zeros);
	*output = joined;
}

static void	hex_prefix(t_conf **conf, char **output, long long number)
{
	char	*joined;

	if (!number)
		return ;
	if ((*conf)->flag_hashtag)
	{
		if ((*conf)->flag_zeropadded && !(*conf)->flag_leftadjusted)
		{
			if ((*conf)->is_uppercase)
				ft_putstr("0X");
			else
				ft_putstr("0x");
			(*conf)->width -= 2;
			(*conf)->n += 2;
			return ;
		}
		joined = ft_strjoin("0x", *output);
		if (!joined)
			ft_printf_exit_error(MSG_ALLOC_FAILED);
		free(*output);
		*output = joined;
	}
}

/*
 * Handles hexadecimal conversion. Treats given numbers as unsigned.
*/
void	conversion_hexadecimal(t_conf **conf)
{
	int					len;
	char				*itoa;
	unsigned long long	number;

	number = get_va_arg_unsigned(conf);
	itoa = ft_itoa_base_ull(number, 16, 0);
	if (!itoa)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	hex_precision(conf, &itoa);
	hex_prefix(conf, &itoa, number);
	len = ft_strlen(itoa);
	if (!number && (*conf)->precision == 0)
		len = 0;
	if ((*conf)->width - len > 0 && !(*conf)->flag_leftadjusted
		&& !(*conf)->flag_zeropadded)
		ft_putchar_n_repeat(' ', &((*conf)->n), (*conf)->width - len);
	if ((*conf)->width - len > 0 && !(*conf)->flag_leftadjusted
		&& (*conf)->flag_zeropadded)
		ft_putchar_n_repeat('0', &((*conf)->n), (*conf)->width - len);
	if (!(!number && (*conf)->precision == 0))
		ft_putstr_n_case(itoa, &((*conf)->n), (*conf)->is_uppercase);
	if ((*conf)->width - len > 0 && (*conf)->flag_leftadjusted)
		ft_putchar_n_repeat(' ', &((*conf)->n), (*conf)->width - len);
	free(itoa);
}

void	conversion_hexadecimal_lower(t_conf **conf)
{
	(*conf)->is_uppercase = 0;
	conversion_hexadecimal(conf);
}

void	conversion_hexadecimal_upper(t_conf **conf)
{
	(*conf)->is_uppercase = 1;
	conversion_hexadecimal(conf);
}
