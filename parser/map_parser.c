/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:03:59 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/31 09:32:22 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_angle(char c)
{
	double	angle;

	angle = 0;
	(c == 'N') ? angle = M_PI_2 : angle;
	(c == 'S') ? angle = 3 * M_PI_2 : angle;
	(c == 'E') ? angle = 0 : angle;
	(c == 'W') ? angle = M_PI : angle;
	return (angle);
}

int		map_parser(int fd, t_params *prms, char **line)
{
	int		i;
	char	*line_map;

	i = 1;
	line_map = NULL;
	while (i)
	{
		line_map = gnl_strjoin(line_map, *line);
		line_map = gnl_strjoin(line_map, "\n");
		free(*line);
		i = get_next_line(fd, line);
	}
	line_map = gnl_strjoin(line_map, *line);
	free(*line);
	((prms->map = map_split(line_map, '\n')) && check_map(prms) &&
		get_player(prms) && get_sprites(prms)) ? i = 1 : 0;
	free(line_map);
	return (i);
}

int		get_player(t_params *prms)
{
	int			i;
	int			j;

	i = 0;
	while (prms->map[i] != 0)
	{
		j = 0;
		while (prms->map[i][j])
		{
			if (ft_strchr("NSWE", prms->map[i][j]))
			{
				if (prms->plr.pos_y > 0 && write(1, DBL_PLR, 27))
					return (0);
				prms->plr.pos_x = (double)j + 0.5;
				prms->plr.pos_y = (double)i + 0.5;
				prms->plr.angle_v = 0;
				prms->plr.ang_h = get_angle(prms->map[i][j]);
			}
			j++;
		}
		i++;
	}
	if (prms->plr.pos_x == 0 && write(1, NO_PLR, 23))
		return (0);
	return (1);
}
