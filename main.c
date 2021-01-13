/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:31 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/13 15:51:16 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	show_parse_res(t_params * params);

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
	if (params->map)
		free(params->map);
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
	t_params	*params;

	if (check_main_input(argc) && (params = parser(argv[1])))
	{
		printf("params - ok\n");
		show_parse_res(params);
		params_free(params);
	}
	else
		printf("params error\n");
}

void	show_parse_res(t_params * params)
{
	printf("hrez = %d\n", params->res_h);
	printf("vrez = %d\n", params->res_v);
	printf("north = \"%s\"\n", params->north);
	printf("south = \"%s\"\n", params->south);
	printf("west = \"%s\"\n", params->west);
	printf("east = \"%s\"\n", params->east);
	printf("sprite = \"%s\"\n", params->sprite);
	printf("f_color_r = %d\n", params->floor_color.red);
	printf("f_color_g = %d\n", params->floor_color.green);
	printf("f_color_b = %d\n", params->floor_color.blue);
	printf("c_color_r = %d\n", params->ceil_color.red);
	printf("c_color_g = %d\n", params->ceil_color.green);
	printf("c_color_b = %d\n", params->ceil_color.blue);
	printf("map:\n%s\n", params->map);
}