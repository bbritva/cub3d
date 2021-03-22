/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:59:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 12:55:42 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * BONUS
 */
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
	if (spr->dist < SPOT_DIST)
		spr->status_mask = spr->status_mask | Z_GOING;
	if (spr->dist > SPOT_DIST)
		spr->status_mask = spr->status_mask & ~(Z_GOING);
	return (0);
}
