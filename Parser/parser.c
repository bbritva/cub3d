/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/07 14:02:38 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

t_params	*params_init()
{
	t_params	*params;

	params = (t_params *)malloc(sizeof(t_params));
	if (params)
	{
		params->res_h = -1;
		params->res_v = -1;
		params->north = NULL;
		params->south = NULL;
		params->west = NULL;
		params->east = NULL;
		params->sprite = NULL;
		params->floor_color.red = -1;
		params->floor_color.green = -1;
		params->floor_color.blue = -1;
		params->ceil_color.red = -1;
		params->ceil_color.green = -1;
		params->ceil_color.blue = -1;
	}
	return (params);
}

int 	parser(char *f_name, t_all *all)
{
	int			fd;
	char		*line;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (0);
	}
	if ((all->prms = params_init()))
	{
		param_parser(fd, all->prms, &line);
		map_parser(fd, all, &line);
		free(line);
		show_parse_res(all);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	show_parse_res(t_all *all)
{
	int i;

	printf("hrez = %d\n", all->prms->res_h);
	printf("vrez = %d\n", all->prms->res_v);
	printf("north = \"%s\"\n", all->prms->north);
	printf("south = \"%s\"\n", all->prms->south);
	printf("west = \"%s\"\n", all->prms->west);
	printf("east = \"%s\"\n", all->prms->east);
	printf("sprite = \"%s\"\n", all->prms->sprite);
	printf("f_color_r = %d\n", all->prms->floor_color.red);
	printf("f_color_g = %d\n", all->prms->floor_color.green);
	printf("f_color_b = %d\n", all->prms->floor_color.blue);
	printf("c_color_r = %d\n", all->prms->ceil_color.red);
	printf("c_color_g = %d\n", all->prms->ceil_color.green);
	printf("c_color_b = %d\n", all->prms->ceil_color.blue);
	i = 0;
	while (*(all->map + i))
		ft_putendl_fd(all->map[i++], 1);
}




