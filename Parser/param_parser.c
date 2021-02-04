/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:58:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/13 18:16:04 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_params	*param_parser(int fd, t_params *params, char **line)
{
	int 	i;

	while ((i = get_next_line(fd, line)) && !is_map_line(*line))
	{
		parse_line(params, *line);
		free(*line);
	}
	return (params);
}
