/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/09 11:23:15 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double		get_dY(t_player *plr, double angle)
{
	t_player	p;

	p = *plr;
	if (angle > 0 && angle < M_PI)
	{
		if (p.pos_y == floor(p.pos_y))
			p.pos_y--;
		else
			p.pos_y = floor(p.pos_y);
	}
	else
	{
		if (p.pos_y == ceil(p.pos_y))
			p.pos_y++;
		else
			p.pos_y = ceil(p.pos_y);
	}
	return ((p.pos_y - plr->pos_y) / sin(angle));
}

double		get_dX(t_player *plr, double angle)
{
	t_player	p;

	p = *plr;
	if (angle > 3 * M_PI_2 || angle < M_PI_2)
	{
		if (p.pos_x == ceil(p.pos_x))
			p.pos_x++;
		else
			p.pos_x = ceil(p.pos_x);
	}
	else
	{
		if (p.pos_x == floor(p.pos_x))
			p.pos_x--;
		else
			p.pos_x = floor(p.pos_x);
	}
	return ((p.pos_x - plr->pos_x) / cos(angle));
}


int		get_height2(t_all *all, double angle)
{
	int 		h;
	int 		dir;
	double		dX;
	double		dY;
	double		dist;
	t_player	p;

	p = all->plr;
	while (all->prms->map[(int) p.pos_y][(int) p.pos_x])
	{
		dX = get_dX(&p, angle);
		dY = get_dY(&p, angle);
		if (fabs(dY) > fabs(dX))
		{
			p.pos_x += dX * cos(angle);
			p.pos_y -= dX * sin(angle);
			dir = NORTH;
			if (is_wall(all, p, angle, 'v'))
				break;
		}
		else
		{
			p.pos_y += dY * sin(angle);
			p.pos_x -= dY * cos(angle);
			dir = SOUTH;
			if (is_wall(all, p, angle, 'h'))
				break;
		}
	}
	dX = p.pos_x - all->plr.pos_x;
	dY = p.pos_y - all->plr.pos_y;
	dist = sqrt(dX * dX + dY * dY);
	dist *= cos(angle - all->plr.ang_h);
	h = (int) (((double)all->prms->res_v / 3) * SCALE / dist) | dir;
	return (h);
}

