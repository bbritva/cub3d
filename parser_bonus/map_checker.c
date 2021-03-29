/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cheker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 19:11:35 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 11:29:44 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/parser.h"

static int	simple_check_line(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!is_map_line(map[i]))
		{
			ft_putstr(MAP_ERR);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_first_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
		if (ft_strchr("4320NSWE", line[i++]))
		{
			ft_putstr(MAP_ERR);
			return (0);
		}
	return (1);
}

static int	check_zero(char **map, int i, int j)
{
	if (ft_strchr("1 ", map[i][j]))
		return (1);
	if (!map[i - 1][j] || map[i - 1][j] == ' ')
		return (0);
	if (!map[i + 1][j] || map[i + 1][j] == ' ')
		return (0);
	if (!map[i][j - 1] || map[i][j - 1] == ' ')
		return (0);
	if (!map[i][j + 1] || map[i][j + 1] == ' ')
		return (0);
	return (1);
}

int			check_map(t_params *prms)
{
	int	i;
	int	j;

	if (!simple_check_line(prms->map))
		return (0);
	if (!check_first_line(prms->map[0]))
		return (0);
	i = 1;
	while (prms->map[i + 1])
	{
		j = 0;
		while (prms->map[i][j])
		{
			if (!check_zero(prms->map, i, j))
			{
				ft_putstr(MAP_ERR);
				return (0);
			}
			j++;
		}
		i++;
	}
	if (!check_first_line(prms->map[i]))
		return (0);
	return (1);
}
