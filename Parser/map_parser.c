/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:03:59 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/26 19:43:11 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
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


int					map_parser(int fd, t_params *prms, char **line)
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
	if (**line)
	{
		line_map = gnl_strjoin(line_map, *line);
		line_map = gnl_strjoin(line_map, "\n");
		free(*line);
	}
	if ((prms->map = map_split(line_map, '\n')) && check_map(prms) &&
		get_player(prms) && get_sprites(prms))
	{
		free(line_map);
//		all->plr.pos_x = 25.5;
//		all->plr.pos_y = 11.2;
//		all->plr.ang_h = M_PI;
		return (1);
	}
	free(line_map);
	return (0);
}

int 	get_player(t_params *prms)
{
	int			i;
	int			j;

	i = 0;
	prms->plr.pos_y = 0;
	while (prms->map[i] != 0)
	{
		j = 0;
		while (prms->map[i][j])
		{
			if (ft_strchr("NSWE",prms->map[i][j]))
			{
				if (prms->plr.pos_y > 0)
					return (0);
				prms->plr.pos_x = (double)j + 0.5;
				prms->plr.pos_y = (double)i + 0.5;
				prms->plr.angle_v = 0;
				(prms->map[i][j] == 'N') ? prms->plr.ang_h = M_PI_2 :
					prms->plr.ang_h;
				(prms->map[i][j] == 'S') ? prms->plr.ang_h = 3 * M_PI_2 :
						prms->plr.ang_h;
				(prms->map[i][j] == 'E') ? prms->plr.ang_h = 0 : prms->plr
						.ang_h;
				(prms->map[i][j] == 'W') ? prms->plr.ang_h = M_PI :
						prms->plr.ang_h;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int 	get_spr_count(char **map)
{
	int			i;
	int			j;
	int 		size;

	size = 0;
	i = 0;
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("2", map[i][j]))
				size++;
			j++;
		}
		i++;
	}
	return (size);
}

int 	get_sprites(t_params *prms)
{
	int			i;
	int			j;
	int			k;
	int 		count;

	count = get_spr_count(prms->map);
	if ((prms->sprites = (t_sprite **)ft_calloc(count + 1,
		sizeof(t_sprite *))))
	{
		i = 0;
		k = 0;
		while (prms->map[i] != 0)
		{
			j = 0;
			while (prms->map[i][j])
			{
				if (ft_strchr("2", prms->map[i][j]) &&
				(prms->sprites[k] = ft_calloc(1, sizeof (t_sprite))))
				{
					prms->sprites[k]->pos_x = j;
					prms->sprites[k]->pos_y = i;
					prms->sprites[k++]->dist = 0;
				}
				j++;
			}
			i++;
		}
		prms->sprites[k] = NULL;
		return (1);
	}
	return (0);
}
