/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:03:59 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/23 10:03:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>
//
//char 	**map_convert(char *char_map, int len, int height)
//{
//	char	**map;
//	int 	i;
//	int 	j;
//
//	if ((map = ft_calloc(height + 1, sizeof(char *))))
//	{
//		i = 0;
//		if ((map[i] = ft_calloc(len + 1, sizeof(char *))))
//		{
//			while (*char_map && *char_map != '\n');
//		}
//
//	}
//	return (map);
//}

int 		check_map(t_params *params)
{
	// int		in_map;
	// char 	**map;
	// int 	i;
	// int 	j;

	(void) params;
	// map = params->map;
	// i = 0;
	// while (map[i])
	// {
	// 	j = 0;
	// 	while (map[i][j] && map[i][j + 1])
	// 	{
	// 		if (map[i][j + 1] == '1' && !ft_strchr("02NSWE", map[i][j]))
	// 			in_map = 1;
	// 		if (!ft_strchr("02NSWE", map[i][j + 1]) && map[i][j] == '1' &&
	// 		in_map)
	// 			in_map = 0;
	// 		j++;
	// 	}
	// 	if (in_map)
	// 		return (0);
	// 	i++;
	// }
	return (1);
}

t_params	*map_parser(int fd, t_params *params, char **line)
{
	int 	i;
	char	*line_map;

	i = 1;
	line_map = NULL;
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