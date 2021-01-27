/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/27 19:18:34 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_height2(t_win *win, float angle)
{
	t_player	p;
	int			h;
	float 		k;
	float 		len;
	float 		dir_X;
	float 		dir_Y;
	float 		step_X;
	float 		step_Y;
	int 		map_X;
	int 		map_Y;
	float 		ray_X;
	float 		ray_Y;
	float 		plane_X;
	float 		plane_Y;

	dir_X = cosf(win->params->player->angle_h);
	dir_Y = -sinf(win->params->player->angle_h);
	ray_X = cosf(angle);
	ray_Y = -sinf(angle);
	plane_X = 2 * dir_Y / 3;
	plane_Y = 2 * dir_X / 3;
	p = *(win->params->player);
	len = 0;
	map_X = (int)p.pos_x;
	map_Y = (int)p.pos_y;

	return (h);
}