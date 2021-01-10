/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/10 15:24:07 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		get_rez(t_params *map, char *line)
{
	int i;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i] != 0)
		i++;
	if (line[i] != 0)
		map->res_h = 0;
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
	{
		map->res_h = map->res_h * 10 + (line[i] - '0');
		i++;
	}
	while ((line[i] < '0' || line[i] > '9') && line[i] != 0)
		i++;
	if (line[i] != 0)
		map->res_v = 0;
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
	{
		map->res_v = map->res_v * 10 + (line[i] - '0');
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

void 	parse_line(t_params *map, char *line)
{
	if (line[0] == 'R')
		get_rez(map, line);
	if (!ft_strncmp("NO", line, 2))
		map->north = get_path(line, map->north);
	if (!ft_strncmp("SO", line, 2))
		map->south = get_path(line, map->south);
	if (!ft_strncmp("WE", line, 2))
		map->west = get_path(line, map->west);
	if (!ft_strncmp("EA", line, 2))
		map->east = get_path(line, map->east);
	if (line[0] == 'S' && line[1] != 'O')
		map->sprite = get_path(line, map->sprite);
	if (line[0] == 'F')
		map->floor_color = get_color(line, map->floor_color);
	if (line[0] == 'C')
		map->ceil_color = get_color(line, map->floor_color);
}

t_params	*map_init()
{
	t_params	*map;

	map = (t_params *)malloc(sizeof(t_params));
	if (map)
	{
		map->res_h = -1;
		map->res_v = -1;
		map->north = NULL;
		map->south = NULL;
		map->west = NULL;
		map->east = NULL;
		map->sprite = NULL;
		map->floor_color.red = -1;
		map->floor_color.green = -1;
		map->floor_color.blue = -1;
		map->ceil_color.red = -1;
		map->ceil_color.green = -1;
		map->ceil_color.blue = -1;
	}
	return (map);
}

t_params	*parser(char *f_name)
{
	int		fd;
	char	*line;
	int		i;
	t_params	*map;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (NULL);
	}
	if ((map = map_init()))
	{
		while ((i = get_next_line(fd, &line)) && !is_map_line(line))
		{
			parse_line(map, line);
			free(line);
		}
		while (is_map_line(line) && i)
		{
			printf("%s\n", line);
//			parse_line(map, line);
			free(line);
			i = get_next_line(fd, &line);
		}
		printf("hrez = %d\n", map->res_h);
		printf("vrez = %d\n", map->res_v);
		printf("north = \"%s\"\n", map->north);
		printf("south = \"%s\"\n", map->south);
		printf("west = \"%s\"\n", map->west);
		printf("east = \"%s\"\n", map->east);
		printf("sprite = \"%s\"\n", map->sprite);
		printf("f_color_r = \"%d\"\n", map->floor_color.red);
		printf("f_color_g = \"%d\"\n", map->floor_color.green);
		printf("f_color_b = \"%d\"\n", map->floor_color.blue);
		printf("c_color_r = \"%d\"\n", map->ceil_color.red);
		printf("c_color_g = \"%d\"\n", map->ceil_color.green);
		printf("c_color_b = \"%d\"\n", map->ceil_color.blue);

		free(line);
		return (map);
	}
	close(fd);
	return (map);
}
