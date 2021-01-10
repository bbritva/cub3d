/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:11:23 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/10 14:07:12 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_map_line(char *line)
{
	int	result;

	result = 1;
	while (line)
		if (!ft_strchr(" 012NSWE", *line++))
			result = 0;
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while ((n > 0) && (*ptr1 || *ptr2))
	{
		if (*ptr1 != *ptr2)
			return ((int)(*ptr1 - *ptr2));
		n--;
		ptr1++;
		ptr2++;
	}
	return (0);
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
