/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:03:59 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/21 10:28:13 by grvelva          ###   ########.fr       */
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

int 		check_map(t_params *prms)
{
	// int		in_map;
	// char 	**map;
	// int 	i;
	// int 	j;

	(void) prms;
	// map = prms->map;
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
	prms->map = map_split(line_map, '\n');//незащищенный маллок
	free(line_map);
	get_player(prms);
	get_sprites(prms);
//	all->plr.pos_x = 25.5;
//	all->plr.pos_y = 11.2;
//	all->plr.ang_h = M_PI;
	if (check_map(prms))
	{
		ft_putstr("map - ok\n");
		return (1);
	}
	ft_putstr("map - error\n");
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
					return (-1);
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

	if (count > 0 && (prms->sprites = (t_sprite **)ft_calloc(count + 1,
															   sizeof(void *))))
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
	}
	return (1);
}
