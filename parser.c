/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/09 18:24:27 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		get_rez(t_map *map, char *line)
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

char 	*get_path(char *line)
{
	int		i;
	int		j;
	char 	*path;

	i = 0;
	while (line[i] && line[i] != '.')
		i++;
	if ((path = (char *)malloc(sizeof(char) * (ft_strlen(&line[i] + 1)))))
	{
		j = 0;
		while(line[i])
			path[j++] = line[i++];
		path[j] = 0;
	}
	return (path);
}

void 	parse_line(t_map *map, char *line)
{
	if (line[0] == 'R')
		get_rez(map, line);
	if (!ft_strncmp("NO", line, 2))
		map->north = get_path(line);
	if (!ft_strncmp("SO", line, 2))
		map->south = get_path(line);
	if (!ft_strncmp("WE", line, 2))
		map->west = get_path(line);
	if (!ft_strncmp("EA", line, 2))
		map->east = get_path(line);
	if (line[0] == 'S')
		map->sprite = get_path(line);
	if (line[0] == 'F')
		map->floor_color = get_color(line, map->floor_color);
	if (line[0] == 'C')
		map->ceil_color = get_color(line, map->floor_color);
}

t_map	*parser(char *f_name)
{
	int		fd;
	char	*line;
	int		i;
	t_map	*map;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (NULL);
	}
	if ((map = (t_map *)malloc(sizeof(t_map))))
	{
		while ((i = get_next_line(fd, &line)))
		{
			parse_line(map, line);
			free(line);
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
