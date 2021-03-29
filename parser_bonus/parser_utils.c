/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:11:23 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 11:29:44 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

int			isclr(int color)
{
	return (color >= 0 && color <= 255);
}

int			is_map_line(char *line)
{
	int	result;

	result = 0;
	if (*line)
		result = 1;
	while (*line)
		if (!ft_strchr(" 01234NSWE", *line++))
			return (0);
	return (result);
}

int			get_color(const char *line, int i, int *color, int *err)
{
	i = skip_spaces(line, i);
	if (ft_isdigit(line[i]))
	{
		*color = 0;
		while (ft_isdigit(line[i]) && *color < 256 && *color >= 0)
			*color = *color * 10 + (line[i++] - '0');
		return (skip_spaces(line, i));
	}
	*err = *err | (1 << 4);
	return (i);
}

int			get_colors(const char *line, int color, int *err)
{
	int i;
	int red;
	int green;
	int blue;

	i = 1;
	if (color != -1)
		*err = *err | (1 << 4);
	i = get_color(line, i, &red, err);
	if (line[i++] != ',')
		*err = *err | (1 << 4);
	i = get_color(line, i, &green, err);
	if (line[i++] != ',')
		*err = *err | (1 << 4);
	i = get_color(line, i, &blue, err);
	i = skip_spaces(line, i);
	if (line[i] || !isclr(red) || !isclr(green) || !isclr(blue))
		*err = *err | (1 << 4);
	return (red << 16 | green << 8 | blue);
}

int			skip_spaces(const char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	return (i);
}
