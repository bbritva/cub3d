/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:58:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/21 12:17:07 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_rez(t_params *params, const char *line)
{
	int i;

	i = 1;
	i = skip_spaces(line, i);
	if (ft_isdigit(line[i]) && params->res_h == -1)
		params->res_h = 0;
	while (ft_isdigit(line[i]))
		params->res_h = params->res_h * 10 + (line[i++] - '0');
	i = skip_spaces(line, i);
	if (ft_isdigit(line[i]) && params->res_v == -1)
		params->res_v = 0;
	while (ft_isdigit(line[i]))
		params->res_v = params->res_v * 10 + (line[i++] - '0');
	i = skip_spaces(line, i);
	if (line[i] != 0)
		params->res_h = -2;
	return (i);
}

int		get_path(char *line, char *path, int i, int *err)
{
	int		j;

	i = skip_spaces(line, i);
	if (path && (*err = *err | 0b1))
		return (0);
	if ((path = ft_calloc(sizeof(char), ft_strlen(&line[i]) + 1)))
	{
		j = 0;
		while(line[i])
			path[j++] = line[i++];
		path[j] = 0;
		return (1);
	}
	return (0);
}

void 	parse_line(t_params *params, char *line, int *err)
{
	if (line[0] == 'R')
		get_rez(params, line);
	if (!ft_strncmp("NO", line, 2) && !get_path(line, params->north, 2, err))
		params->north = NULL;
	if (!ft_strncmp("SO", line, 2) && !get_path(line, params->south, 2, err))
		params->south = NULL;
	if (!ft_strncmp("WE", line, 2) && !get_path(line, params->west, 2, err))
		params->west = NULL;
	if (!ft_strncmp("EA", line, 2) && !get_path(line, params->east, 2, err))
		params->east = NULL;
	if (!ft_strncmp("S", line, 1) && !get_path(line, params->sprite, 1, err))
		params->sprite = NULL;
	if (line[0] == 'F')
		params->floor_color = get_color(line, params->floor_color);
	if (line[0] == 'C')
		params->ceil_color = get_color(line, params->ceil_color);
}

double 		*dists_init(int size)
{
	double	*dists;

	if (size > 0 && (dists = (double *)ft_calloc(size, sizeof (double))))
		return (dists);
	return (NULL);
}

t_params	*param_parser(int fd, t_params *prms, char **line, int *err)
{
	while ((get_next_line(fd, line)) && !is_map_line(*line))
	{
		parse_line(prms, *line, err);
		free(*line);
	}
	prms->dists = dists_init(prms->res_h);
	return (prms);
}
