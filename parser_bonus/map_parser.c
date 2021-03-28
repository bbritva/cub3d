/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:03:59 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 09:03:01 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

double		get_angle(char c)
{
	double	angle;

	angle = 0;
	(c == 'N') ? angle = M_PI_2 : angle;
	(c == 'S') ? angle = 3 * M_PI_2 : angle;
	(c == 'E') ? angle = 0 : angle;
	(c == 'W') ? angle = M_PI : angle;
	return (angle);
}

t_player	init_player(int j, int i, char dir)
{
	t_player p;

	p.pos_x = (double)j + 0.5;
	p.pos_y = (double)i + 0.5;
	p.health = 100;
	p.status_mask = 0;
	p.ang_h = get_angle(dir);
	return (p);
}

int			map_parser(int fd, t_params *prms, char **line)
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

int			get_player(t_params *prms)
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
				if (prms->plr.pos_y > 0 && write(1,
					"Error\nDouble player\n", 20))
					return (0);
				prms->plr = init_player(j, i, prms->map[i][j]);
			}
			j++;
		}
		i++;
	}
	if (prms->plr.pos_x == 0 && write(1, "Error\nNo player\n", 16))
		return (0);
	return (1);
}
