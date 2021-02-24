/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/24 15:15:49 by grvelva          ###   ########.fr       */
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


int		get_height(t_all *all, int i)
{
	int 		h;
	int 		dir;
	int 		x_coor;
	double		dX;
	double		dY;
	double		dist;
	t_player	p;
	double		angle;

	p = all->prms->plr;
	angle = all->prms->plr.ang_h + M_PI / 6 - i * (M_PI / (3 *
													 all->prms->res_h));
	(angle < 0) ? angle += 2 * M_PI : angle;
	(angle > 2 * M_PI) ? angle -= 2 * M_PI : angle;
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
	dX = p.pos_x - all->prms->plr.pos_x;
	dY = p.pos_y - all->prms->plr.pos_y;
	dist = sqrt(dX * dX + dY * dY);
	dist *= cos(angle - all->prms->plr.ang_h);
	all->prms->dists[i] = dist;
	dX = (all->prms->res_h > all->prms->res_v) ? all->prms->res_v :
			all->prms->res_h;
	h = (int) ((dX / 1.0) * SCALE / dist);
	return (h | dir | (x_coor << 16));
}

//сложный кастер для спрайтов
//int		get_spr_prms(t_all *all, double angle)
//{
//	int 		h;
//	int 		x_coor;
//	double		dX;
//	double		dY;
//	double		dist;
//	t_player	p;
//
//	p = all->plr;
//	while (all->prms->map[(int) p.pos_y][(int) p.pos_x])
//	{
//		dX = get_dX(&p, angle);
//		dY = get_dY(&p, angle);
//		if (fabs(dY) > fabs(dX))
//		{
//			p.pos_x += dX * cos(angle);
//			p.pos_y -= dX * sin(angle);
//			x_coor = (int) ((p.pos_y - floor(p.pos_y)) * 255);
//			if (is_wall(all, p, angle, 'v'))
//				return (0);
//			if (is_sprite(all, p, angle, 'v'))
//				break;
//		}
//		else
//		{
//			p.pos_y += dY * sin(angle);
//			p.pos_x -= dY * cos(angle);
//			x_coor = (int) ((p.pos_x - floor(p.pos_x)) * 255);
//			if (is_wall(all, p, angle, 'v'))
//				return (0);
//			if (is_sprite(all, p, angle, 'h'))
//				break;
//		}
//	}
//	dX = ceil(p.pos_x) - 0.5 - all->plr.pos_x;
//	dY = ceil(p.pos_y) - 0.5 - all->plr.pos_y;
//	dist = sqrt(dX * dX + dY * dY);
//	dist *= cos(angle - all->plr.ang_h);
//	h = (int) (((double)all->prms->res_v / 1.2) * SCALE / dist);
//	return (h | (x_coor << 16));
//}


//упрощенный кастер для спрайтов
//double		get_wall_dist(t_all *all, double angle)
//{
//	double		dX;
//	double		dY;
//	double		dist;
//	t_player	p;
//
//	p = all->prms->plr;
//	while (all->prms->map[(int) p.pos_y][(int) p.pos_x])
//	{
//		p.pos_x += 0.1 * cos(angle);
//		p.pos_y -= 0.1 * sin(angle);
//		if (is_wall(all, p, angle, 'v'))
//			break;
//	}
//	dX = p.pos_x - all->prms->plr.pos_x;
//	dY = p.pos_y - all->prms->plr.pos_y;
//	dist = sqrt(dX * dX + dY * dY);
//	dist *= cos(angle - all->prms->plr.ang_h);
//	return (dist);
//}

//кастер для конкретного спрайта
int		set_spr_prms(t_sprite *spr,  t_player plr)
{
	double		dX;
	double		dY;

	dX = ceil(spr->pos_x) + 0.5 - plr.pos_x;
	dY = ceil(spr->pos_y) + 0.5 - plr.pos_y;
	spr->angle = atan2(-dY, dX);
	while (spr->angle < 0)
		spr->angle += 2 * M_PI;
	while (spr->angle > 2 * M_PI)
		spr->angle -= 2 * M_PI;
//	if (fabs(plr.ang_h - spr->angle) > M_PI / 6)
//		return (0);
//	x_coor = (int) ((0.5 - (dX * sin(p.ang_h) + dY * cos(p.ang_h))) * 255);
	spr->dist = sqrt(pow(dX, 2) + pow(dY, 2));
//	h = (int) (((double)200 / 1.2) * SCALE / spr->dist);
	return (0);
}

