/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:20:39 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/19 15:02:40 by bbritva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int 		check_map(t_params *params)
{
	int		in_map;
	char 	**map;
	int 	i;
	int 	j;

	map = ft_split(params->map, '\n');
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j + 1])
		{
			if (map[i][j + 1] == '1' && !ft_strchr("02NSWE", map[i][j]))
				in_map = 1;
			if (!ft_strchr("02NSWE", map[i][j + 1]) && map[i][j] == '1' &&
			in_map)
				in_map = 0;
			j++;
		}
		if (in_map)
			return (0);
		i++;
	}
	return (1);
}

t_params	*map_parser(int fd, t_params *params, char **line)
{
	int 	i;
	char	*line_map

	i = 1;
	while (is_map_line(*line) && i)
	{
		line_map = gnl_strjoin(line_map, *line);
		line_map = gnl_strjoin(line_map, "\n");
		free(*line);
		i = get_next_line(fd, line);
	}
	params->map = map_split(line_map, '\n');
	if (check_map(params))
	{
		printf("map - ok\n");
		return (params);
	}
	printf("map - error\n");
	return (params);
}