/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:11:23 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/19 11:25:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_map_line(char *line)
{
	int	result;

	result = 0;
	if (*line)
		result = 1;
	while (*line)
		if (!ft_strchr(" 012NSWE", *line++))
			return (0);
	return (result);
}

int			get_color(const char *line, int color)
{
	int i;
	int red;
	int green;
	int blue;

	i = 0;
	if (color != -1)
		return (-1);
	while ((line[i] < '0' || line[i] > '9') && line[i] != 0)
		i++;
	if (line[i] != 0)
		red = 0;
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
		red = red * 10 + (line[i++] - '0');
	if (line[i] == ',')
	{
		green = 0;
		i++;
	}
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
		green = green * 10 + (line[i++] - '0');
	if (line[i] == ',')
	{
		blue = 0;
		i++;
	}
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
		blue = blue * 10 + (line[i++] - '0');
	return (red << 16 | green << 8 | blue);
}

int		skip_spaces(const char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13 ) || str[i] == 32)
		i++;
	return (i);
}

