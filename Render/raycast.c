/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/27 18:18:42 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_height2(t_win *win, float angle)
{
	t_player	p;
	int			h;
	float 		k;
	float 		dirX;
	float 		dirY;
	float 		stepX;
	float 		stepY;
	float 		ray_dirX;
	float 		ray_dirY;
	float 		camX;
	float 		camY;

	dirX = cosf(win->params->player->angle_h);
	dirY = - sinf(win->params->player->angle_h);
	ray_dirX = cosf(angle);
	ray_dirY = - sinf(angle);
	camX = dirY / 3;
	camY = dirX / 3;
	p = *(win->params->player);

	while (win->params->map[(int) (p.pos_y / SCALE)][(int) (p.pos_x / SCALE)] != '1')
	{
		p.pos_x += 0.05f * cosf(angle);
		p.pos_y -= 0.05f * sinf(angle);
	}
	p.pos_x -= win->params->player->pos_x;
	p.pos_y -= win->params->player->pos_y;
	k = cosf(angle - win->params->player->angle_h);
	h = (int) (5000 / (sqrtf((p.pos_x * p.pos_x) + (p.pos_y * p.pos_y)) * k));
	return (h);
}