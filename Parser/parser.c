/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/21 10:13:33 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int		params_init(t_params *params)
{
	if (params)
	{
		params->res_h = -1;
		params->res_v = -1;
		params->north = NULL;
		params->south = NULL;
		params->west = NULL;
		params->east = NULL;
		params->sprite = NULL;
		params->dists = NULL;
		params->floor_color = -1;
		params->ceil_color = -1;
		return (1);
	}
	return (0);
}

int 	parser(char *f_name, t_params *prms)
{
	int			fd;
	char		*line;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (0);
	}
	if (params_init(prms))
	{
		param_parser(fd, prms, &line);
//		check_params(prms);
		map_parser(fd, prms, &line);
		show_parse_res(prms);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	show_parse_res(t_params *prms)
{
	int i;

	printf("hrez = %d\n", prms->res_h);
	printf("vrez = %d\n", prms->res_v);
	printf("north = \"%s\"\n", prms->north);
	printf("south = \"%s\"\n", prms->south);
	printf("west = \"%s\"\n", prms->west);
	printf("east = \"%s\"\n", prms->east);
	printf("sprite = \"%s\"\n", prms->sprite);
	printf("f_color = %d\n", prms->floor_color);
	printf("c_color = %d\n", prms->ceil_color);
	i = 0;
	while (*(prms->map + i))
		ft_putendl_fd(prms->map[i++], 1);
}




