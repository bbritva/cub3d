/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/11 19:14:07 by grvelva          ###   ########.fr       */
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


int		get_height(t_all *all, double angle)
{
	int 		h;
	int 		dir;
	int 		x_coor;
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
			x_coor = (int) ((p.pos_y - floor(p.pos_y)) * 255);
			dir = (angle > M_PI_2 && angle < 3 * M_PI_2) ? WEST : EAST;
			if (is_wall(all, p, angle, 'v'))
				break;
		}
		else
		{
			p.pos_y += dY * sin(angle);
			p.pos_x -= dY * cos(angle);
			x_coor = (int) ((p.pos_x - floor(p.pos_x)) * 255);
			dir = (angle > 0 && angle < M_PI) ? NORTH : SOUTH;
			if (is_wall(all, p, angle, 'h'))
				break;
		}
	}
	dX = p.pos_x - all->plr.pos_x;
	dY = p.pos_y - all->plr.pos_y;
	dist = sqrt(dX * dX + dY * dY);
	dist *= cos(angle - all->plr.ang_h);
	h = (int) (((double)all->prms->res_v / 1.2) * SCALE / dist);
	return (h | dir | (x_coor << 16));
}


int		get_spr_prms(t_all *all, int i)
{
	int 		h;
	int 		x_coor;
	double		cX;
	double		cY;
	double		dX;
	double		dY;
	double		dist;
	double		angle;
	double		b_angle;
	t_player	p;

	angle = all->plr.ang_h + M_PI / 6 - i * (M_PI / (3 *
													 all->prms->res_h));
	(angle < 0) ? angle += 2 * M_PI : angle;
	(angle > 2 * M_PI) ? angle -= 2 * M_PI : angle;
	p = all->plr;
	while (all->prms->map[(int) p.pos_y][(int) p.pos_x] != '1')
	{
		p.pos_x += 0.05 * cos(angle);
		p.pos_y -= 0.05 * sin(angle);
		if (all->prms->map[(int) p.pos_y][(int) p.pos_x] == '2')
			break;
	}
	if (all->prms->map[(int) p.pos_y][(int) p.pos_x] == '2')
	{

		cX = floor(p.pos_x) + 0.5;
		cY = floor(p.pos_y) + 0.5;
		cX -= all->plr.pos_x;
		cY -= all->plr.pos_y;
		dX = p.pos_x - all->plr.pos_x;
		dY = p.pos_x - all->plr.pos_y;
		dist = sqrt(cX * cX + cY * cY);
		dist *= cos(angle - all->plr.ang_h);
		b_angle = atan2(dX, -dY);
		h = (int) (((double) all->prms->res_v / 2) * SCALE / dist);
		x_coor = (int) fabs((dist * sin(b_angle)) * 255);

		return (h | (x_coor << 16));
		return (h);
	}
	return (0);
}

