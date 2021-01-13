/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/13 15:46:45 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	show_parse_res(t_params * params);

int		get_rez(t_params *params, char *line)
{
	int i;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i] != 0)
		i++;
	if (line[i] != 0)
		params->res_h = 0;
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
	{
		params->res_h = params->res_h * 10 + (line[i] - '0');
		i++;
	}
	while ((line[i] < '0' || line[i] > '9') && line[i] != 0)
		i++;
	if (line[i] != 0)
		params->res_v = 0;
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
	{
		params->res_v = params->res_v * 10 + (line[i] - '0');
		i++;
	}
	return (i);
}

char 	*get_path(char *line, char *path)
{
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != '.')
		i++;
	if (path)
		return (NULL);
	if ((path = (char *)malloc(sizeof(char) * (ft_strlen(&line[i] + 1)))))
	{
		j = 0;
		while(line[i])
			path[j++] = line[i++];
		path[j] = 0;
	}
	return (path);
}

void 	parse_line(t_params *params, char *line)
{
	if (line[0] == 'R')
		get_rez(params, line);
	if (!ft_strncmp("NO", line, 2))
		params->north = get_path(line, params->north);
	if (!ft_strncmp("SO", line, 2))
		params->south = get_path(line, params->south);
	if (!ft_strncmp("WE", line, 2))
		params->west = get_path(line, params->west);
	if (!ft_strncmp("EA", line, 2))
		params->east = get_path(line, params->east);
	if (line[0] == 'S' && line[1] != 'O')
		params->sprite = get_path(line, params->sprite);
	if (line[0] == 'F')
		params->floor_color = get_color(line, params->floor_color);
	if (line[0] == 'C')
		params->ceil_color = get_color(line, params->floor_color);
}

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
	int			i;
	t_params	*params;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (NULL);
	}
	if ((params = params_init()))
	{
		while ((i = get_next_line(fd, &line)) && !is_map_line(line))
		{
			parse_line(params, line);
			free(line);
		}
		while (is_map_line(line) && i)
		{
			params->map = gnl_strjoin(params->map, line);
			params->map = gnl_strjoin(params->map, "\n");
			free(line);
			i = get_next_line(fd, &line);
		}
		show_parse_res(params);
		free(line);
		return (params);
	}
	close(fd);
	return (params);
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


