/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:58:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/24 08:43:32 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_rez(t_params *params, const char *line, int *err)
{
	int i;

	i = 1;
	i = skip_spaces(line, i);
	if (params->res_v != -1 || params->res_h != -1)
		*err = *err | (1 << 1);
	if (ft_isdigit(line[i]) && params->res_h == -1)
		params->res_h = 0;
	while (ft_isdigit(line[i]) && params->res_h < 8000)
		params->res_h = params->res_h * 10 + (line[i++] - '0');
	*err = (params->res_h > 8000) ? *err | (1 << 1) : *err;
	i = skip_spaces(line, i);
	if (ft_isdigit(line[i]) && params->res_v == -1)
		params->res_v = 0;
	while (ft_isdigit(line[i]) && params->res_v < 8000)
		params->res_v = params->res_v * 10 + (line[i++] - '0');
	*err = (params->res_v > 8000) ? *err | (1 << 1) : *err;
	i = skip_spaces(line, i);
	*err = (line[i] != 0) ? *err | (1 << 1) : *err;
	return (i);
}

char	*get_path(char *line, char *path, int i, int *err)
{
	int		j;

	i = skip_spaces(line, i);
	if (path && (*err = *err | (1 << 3)))
		return (0);
	if ((path = ft_calloc(ft_strlen(&line[i]) + 1, sizeof(char))))
	{
		j = 0;
		while(line[i])
			path[j++] = line[i++];
		path[j] = 0;
		return (path);
	}
	return (0);
}

void 	parse_line(t_params *params, char *line, int *err)
{
	if (line[0] == 'R')
		get_rez(params, line, err);
	if (!ft_strncmp("NO", line, 2))
		params->north = get_path(line, params->north, 2, err);
	if (!ft_strncmp("SO", line, 2))
		params->south = get_path(line, params->south, 2, err);
	if (!ft_strncmp("WE", line, 2))
		params->west = get_path(line, params->west, 2, err);
	if (!ft_strncmp("EA", line, 2))
		params->east = get_path(line, params->east, 2, err);
	if (!ft_strncmp("S ", line, 2))
		params->sprite = get_path(line, params->sprite, 1, err);
	if (line[0] == 'F')
		params->floor_color = get_colors(line, params->floor_color, err);
	if (line[0] == 'C')
		params->ceil_color = get_colors(line, params->ceil_color, err);
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
