/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:58:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 11:29:44 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

int			skip_nums(const char *str, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}

int			get_rez(t_params *params, const char *line, int *err)
{
	int i;

	i = skip_spaces(line, 1);
	if (params->res_v != -1 || params->res_h != -1)
		*err = *err | (1 << 1);
	if (ft_isdigit(line[i]) && params->res_h == -1)
		params->res_h = 0;
	while (ft_isdigit(line[i]) && params->res_h < RES_MAX)
		params->res_h = params->res_h * 10 + (line[i++] - '0');
	params->res_h = (params->res_h > RES_MAX) ? RES_MAX : params->res_h;
	params->res_h = (params->res_h < RES_MIN && params->res_h != -1) ?
			RES_MIN : params->res_h;
	i = skip_nums(line, i);
	i = skip_spaces(line, i);
	if (ft_isdigit(line[i]) && params->res_v == -1)
		params->res_v = 0;
	while (ft_isdigit(line[i]) && params->res_v < RES_MAX)
		params->res_v = params->res_v * 10 + (line[i++] - '0');
	params->res_v = (params->res_v > RES_MAX) ? RES_MAX : params->res_v;
	params->res_v = (params->res_v < RES_MIN && params->res_v != -1) ?
			RES_MIN : params->res_v;
	i = skip_nums(line, i);
	i = skip_spaces(line, i);
	*err = (line[i] != 0) ? *err | (1 << 1) : *err;
	return (i);
}

char		*get_path(char *line, char *path, int i, int *err)
{
	int		j;

	i = skip_spaces(line, i);
	if (path && (*err = *err | (1 << 3)))
		free(path);
	if ((path = ft_calloc(ft_strlen(&line[i]) + 1, sizeof(char))))
	{
		j = 0;
		while (line[i])
			path[j++] = line[i++];
		path[j] = 0;
		return (path);
	}
	return (0);
}

void		parse_line(t_params *params, char *line, int *err)
{
	if (line[0] == 'R')
		get_rez(params, line, err);
	if (!ft_strncmp("NO ", line, 3))
		params->north = get_path(line, params->north, 2, err);
	if (!ft_strncmp("SO ", line, 3))
		params->south = get_path(line, params->south, 2, err);
	if (!ft_strncmp("WE ", line, 3))
		params->west = get_path(line, params->west, 2, err);
	if (!ft_strncmp("EA ", line, 3))
		params->east = get_path(line, params->east, 2, err);
	if (!ft_strncmp("S ", line, 2))
		params->sprite = get_path(line, params->sprite, 1, err);
	if (line[0] == 'F')
		params->floor_color = get_colors(line, params->floor_color, err);
	if (line[0] == 'C')
		params->ceil_color = get_colors(line, params->ceil_color, err);
}

t_params	*param_parser(int fd, t_params *prms, char **line, int *err)
{
	int ret;

	while (((ret = get_next_line(fd, line)) > 0) && !is_map_line(*line))
	{
		parse_line(prms, *line, err);
		free(*line);
	}
	*err = (ret == -1) ? *err | (1 << 6) : *err;
	prms->dists = (double *)ft_calloc(prms->res_h, sizeof(double));
	return (prms);
}
