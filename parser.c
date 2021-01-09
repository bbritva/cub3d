/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/09 14:51:17 by grvelva          ###   ########.fr       */
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

void 	parse_line(t_map *map, char *line)
{
	if (line[0] == 'R')
	{
		line += get_rez(map, line);
	}
	(void) map;
	(void) line;
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
			printf("hrez = %d\n", map->res_h);
			printf("vrez = %d\n", map->res_v);
			free(line);
		}
		printf("GNL result = %d\nline =\n%s\n", i, line);
		free(line);
		return (map);
	}
	close(fd);
	return (map);
}
