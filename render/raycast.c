/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:43:13 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	get_dy(t_player *plr, double angle)
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

static double	get_dx(t_player *plr, double angle)
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

static double	get_ang(t_all *all, int i)
{
	double		ang;

	ang = all->prms->plr.ang_h + M_PI / 6 - i * (M_PI / (3 * all->prms->res_h));
	(ang < 0) ? ang += 2 * M_PI : ang;
	(ang > 2 * M_PI) ? ang -= 2 * M_PI : ang;
	return (ang);
}

static int		do_mgc(t_player *p, double ang, double d, char dir)
{
	int mgc;

	if (dir == 'x')
	{
		p->pos_x += d * cos(ang);
		p->pos_y -= d * sin(ang);
		mgc = ((int)((p->pos_y - floor(p->pos_y)) * 255) << 16);
		mgc = (ang > M_PI_2 && ang < 3 * M_PI_2) ? mgc | WEST : mgc | EAST;
	}
	else
	{
		p->pos_y += d * sin(ang);
		p->pos_x -= d * cos(ang);
		mgc = ((int)((p->pos_x - floor(p->pos_x)) * 255) << 16);
		mgc = (ang > 0 && ang < M_PI) ? mgc | NORTH : mgc | SOUTH;
	}
	return (mgc);
}

int				get_height(t_all *all, int i)
{
	int			mgc;
	double		dx;
	double		dy;
	t_player	p;
	double		ang;

	p = all->prms->plr;
	ang = get_ang(all, i);
	while (all->prms->map[(int)p.pos_y][(int)p.pos_x])
	{
		dx = get_dx(&p, ang);
		dy = get_dy(&p, ang);
		if (fabs(dy) > fabs(dx))
			if ((mgc = do_mgc(&p, ang, dx, 'x')) && is_wall(all, p, ang, 'v'))
				break ;
		if (fabs(dy) <= fabs(dx))
			if ((mgc = do_mgc(&p, ang, dy, 'y')) && is_wall(all, p, ang, 'h'))
				break ;
	}
	all->prms->dists[i] = sqrt(pow(p.pos_x - all->prms->plr.pos_x, 2) + pow(
		p.pos_y - all->prms->plr.pos_y, 2)) * cos(ang - all->prms->plr.ang_h);
	return ((int)((double)all->prms->res_h / 2 / tan(M_PI / 6) /
		all->prms->dists[i]) | mgc);
}
