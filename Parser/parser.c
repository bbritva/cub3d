/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/13 18:29:34 by grvelva          ###   ########.fr       */
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
		params->map = NULL;
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
		return (params);
	}
	close(fd);
	return (params);
}



