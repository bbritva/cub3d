/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:31 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/07 15:39:08 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	params_free(t_params *params)
{
	if (params->sprite)
		free(params->sprite);
	if (params->north)
		free(params->north);
	if (params->south)
		free(params->south);
	if (params->west)
		free(params->west);
	if (params->east)
		free(params->east);
	free(params);
}

void	ft_putstr(char *str)
{
	while (*str != 0)
	{
		write(1, str, 1);
		str++;
	}
}

int		check_main_input(int argc)
{
	if (argc == 1)
	{
		ft_putstr(F_MISS_MSG);
		return (0);
	}
	if (argc > 2)
	{
		ft_putstr(M_ARGS_MSG);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all	*all;

	if ((all = (t_all *)malloc(sizeof (t_all))))
	{
		if (check_main_input(argc) && (parser(argv[1], all)))
		{
			ft_putstr("prms - ok\n");
			render(all);
			params_free(all->prms);
		} else
			ft_putstr("prms error\n");
		free(all);
	}
	ft_putstr("end of cub3d\n");
}
