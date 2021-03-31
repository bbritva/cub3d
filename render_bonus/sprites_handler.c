/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:59:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/31 09:51:37 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

int			set_spr_prms(t_sprite *spr, t_player plr)
{
	double	dx;
	double	dy;

	dx = spr->pos_x - plr.pos_x;
	dy = spr->pos_y - plr.pos_y;
	spr->angle = atan2(-dy, dx);
	while (spr->angle < 0)
		spr->angle += 2 * M_PI;
	while (spr->angle > 2 * M_PI)
		spr->angle -= 2 * M_PI;
	spr->dist = sqrt(pow(dx, 2) + pow(dy, 2));
	if (spr->dist < SPOT_DIST && spr->status_mask & Z_ALIVE)
		spr->status_mask = spr->status_mask | Z_GOING;
	if (spr->dist > SPOT_DIST && spr->status_mask & Z_ALIVE)
		spr->status_mask = spr->status_mask & ~(Z_GOING);
	return (0);
}

static void	move_door(t_sprite *spr)
{
	unsigned int dist;

	if (spr->status_mask & Z_GOING)
	{
		spr->pos_x += 0.05;
		dist = ((spr->status_mask >> 15) + 1);
		spr->status_mask = spr->status_mask & ~(0b1111 << 15);
		spr->status_mask = spr->status_mask | (dist << 15);
	}
}

void		move_doors(t_all *all)
{
	int i;

	i = 0;
	while (all->prms->sprites[i])
	{
		if (all->prms->sprites[i]->status_mask & Z_DOOR &&
			(all->prms->sprites[i]->status_mask >> 15) < 20 &&
			all->prms->sprites[i]->status_mask & Z_GOING)
		{
			move_door(all->prms->sprites[i]);
			if (((all->prms->sprites[i]->status_mask >> 15) == 9))
				all->prms->map[(int)all->prms->sprites[i]->pos_y][(int)all->prms
			->sprites[i]->pos_x] = '0';
		}
		i++;
	}
}
