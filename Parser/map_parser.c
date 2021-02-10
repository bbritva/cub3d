/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:03:59 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/10 21:55:40 by grvelva          ###   ########.fr       */
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

int 		check_map(t_all *all)
{
	// int		in_map;
	// char 	**map;
	// int 	i;
	// int 	j;

	(void) all;
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

int 		map_parser(int fd, t_all *all, char **line)
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
	all->prms->map = map_split(line_map, '\n');//незащищенный маллок
	free(line_map);
	get_player(all);
//	all->plr.pos_x = 25.2;
//	all->plr.pos_y = 11.0;
	all->plr.ang_h = M_PI_4;
	if (check_map(all))
	{
		ft_putstr("map - ok\n");
		return (1);
	}
	ft_putstr("map - error\n");
	return (0);
}

int 	get_player(t_all *all)
{
	int			i;
	int			j;
//	t_player	p;

	i = 0;
	all->plr.pos_y = 0;
	while (all->prms->map[i] != 0)
	{
		j = 0;
		while (all->prms->map[i][j])
		{
			if (ft_strchr("NSWE",all->prms->map[i][j]))
			{
				if (all->plr.pos_y > 0)
				{
//					free(all->plr);
					return (-1);
				}
//				if ((all->plr = (t_player *)malloc(sizeof(t_player))))
//				{
					all->plr.pos_x = (double)j + 0.5;
					all->plr.pos_y = (double)i + 0.5;
					all->plr.angle_v = 0;
					(all->prms->map[i][j] == 'N') ? all->plr.ang_h = M_PI_2 :
							all->plr.ang_h;
					(all->prms->map[i][j] == 'S') ? all->plr.ang_h = 3 *
							M_PI_2 :
							all->plr.ang_h;
					(all->prms->map[i][j] == 'E') ? all->plr.ang_h = 0 :
							all->plr.ang_h;
					(all->prms->map[i][j] == 'W') ? all->plr.ang_h = M_PI :
							all->plr.ang_h;
//				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
