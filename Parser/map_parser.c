/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:20:39 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/13 18:20:39 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_params	*map_parser(int fd, t_params *params, char **line)
{
	int 	i;

	i = 1;
	while (is_map_line(*line) && i)
	{
		params->map = gnl_strjoin(params->map, *line);
		params->map = gnl_strjoin(params->map, "\n");
		free(*line);
		i = get_next_line(fd, line);
	}
	return (params);
}