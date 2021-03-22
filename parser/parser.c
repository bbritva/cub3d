/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 10:54:06 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>


void	show_parse_res(t_params * params);

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
		params->map = NULL;
		params->player = NULL;
		params->floor_color.red = -1;
		params->floor_color.green = -1;
		params->floor_color.blue = -1;
		params->ceil_color.red = -1;
		params->ceil_color.green = -1;
		params->ceil_color.blue = -1;
	}
	return (params);
}

t_params	*parser(char *f_name)
{
	int			fd;
	char		*line;
	t_params	*params;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (NULL);
	}
	if ((params = params_init()))
	{
		params = param_parser(fd, params, &line);
		params = map_parser(fd, params, &line);
		free(line);
		show_parse_res(params);
		return (params);
	}
	close(fd);
	return (params);
}

void	show_parse_res(t_params * params)
{
	int i;

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
	i = 0;
	while (*(params->map + i))
		printf("%s\n", params->map[i++]);
}




