/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:51:17 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/23 17:42:57 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int 	show_param_errors(const int *err)
{
	if (*err & (1 << 0))
		ft_putstr("None resolution parameters\n");
	if (*err & (1 << 1))
		ft_putstr("Multiple resolution parameters\n");
	if (*err & (1 << 2))
		ft_putstr("Not enough texture parameters\n");
	if (*err & (1 << 3))
		ft_putstr("Multiple texture parameters\n");
	if (*err & (1 << 4))
		ft_putstr("None or wrong ceiling/floor color parameters\n");
	if (*err & (1 << 5))
		ft_putstr("Memory allocating error\n");
	return(0);
}

int 	free_params(t_params *params, int *err)
{
	if (params->north)
		free (params->north);
	if (params->south)
		free (params->south);
	if (params->west)
		free (params->west);
	if (params->east)
		free (params->east);
	if (params->sprite)
		free (params->sprite);
	free(params);
	if (*err)
		show_param_errors(err);
	return (0);
}

int 	check_params(t_params *params, int *err)
{
	*err = (params->res_h == -1 || params->res_v == -1) ? *err | 1 : *err;
	*err = (params->north) ? *err : *err | (1 << 2);
	*err = (params->south) ? *err : *err | (1 << 2);
	*err = (params->west) ? *err : *err | (1 << 2);
	*err = (params->east) ? *err : *err | (1 << 2);
	*err = (params->sprite) ? *err : *err | (1 << 2);
	return (1);
}

int		params_init(t_params *params)
{
	if (params)
	{
		params->res_h = -1;
		params->res_v = -1;
		params->north = NULL;
		params->south = NULL;
		params->west = NULL;
		params->east = NULL;
		params->sprite = NULL;
		params->dists = NULL;
		params->floor_color = -1;
		params->ceil_color = -1;
		return (1);
	}
	return (0);
}

int 	parser(char *f_name, t_params *prms)
{
	int			fd;
	int 		err;
	char		*line;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (0);
	}
	if (params_init(prms))
	{
		err = 0;
		param_parser(fd, prms, &line, &err);
		check_params(prms, &err);
		if (err)
			free_params(prms, &err);
		else
		{
			map_parser(fd, prms, &line);
			show_parse_res(prms);
			close(fd);
			return (1);
		}
	}
	close(fd);
	return (0);
}

void	show_parse_res(t_params *prms)
{
	int i;

	printf("hrez = %d\n", prms->res_h);
	printf("vrez = %d\n", prms->res_v);
	printf("north = \"%s\"\n", prms->north);
	printf("south = \"%s\"\n", prms->south);
	printf("west = \"%s\"\n", prms->west);
	printf("east = \"%s\"\n", prms->east);
	printf("sprite = \"%s\"\n", prms->sprite);
	printf("f_color = %d\n", prms->floor_color);
	printf("c_color = %d\n", prms->ceil_color);
	i = 0;
	while (*(prms->map + i))
		ft_putendl_fd(prms->map[i++], 1);
}




