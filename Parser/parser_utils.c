/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:11:23 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/05 18:49:23 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_color get_color(char *line, t_color color)
{

	int i;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i] != 0)
		i++;
	if (line[i] != 0)
		color.red = 0;
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
		color.red = color.red * 10 + (line[i++] - '0');
	if (line[i] == ',')
	{
		color.green = 0;
		i++;
	}
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
		color.green = color.green * 10 + (line[i++] - '0');
	if (line[i] == ',')
	{
		color.blue = 0;
		i++;
	}
	while ((line[i] >= '0' && line[i] <= '9') && line[i] != 0)
		color.blue = color.blue * 10 + (line[i++] - '0');
	return (color);
}
