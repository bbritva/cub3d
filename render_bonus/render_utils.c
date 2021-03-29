/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:59:41 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/29 11:31:50 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

void		my_pixel_put(t_win *win, int x, int y, unsigned int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

static int	set_horizontal_intersect(int *x, int *y, double angle,
								t_player p)
{
	if (angle > 0 && angle < M_PI)
	{
		*x = (int)p.pos_x;
		*y = (int)(p.pos_y - 1);
	}
	else
	{
		*x = (int)p.pos_x;
		*y = (int)p.pos_y;
	}
	return (0);
}

static int	set_vertical_intersect(int *x, int *y, double angle, t_player p)
{
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		*x = (int)(p.pos_x - 1);
		*y = (int)p.pos_y;
	}
	else
	{
		*x = (int)p.pos_x;
		*y = (int)p.pos_y;
	}
	return (0);
}

int			is_wall(t_all *all, t_player p, double angle, char hv)
{
	int	x;
	int	y;

	if (hv == 'h')
		set_horizontal_intersect(&x, &y, angle, p);
	else
		set_vertical_intersect(&x, &y, angle, p);
	if ('1' != all->prms->map[y][x])
		return (0);
	return (1);
}

int			crop_resolution(t_all *all)
{
	int res_h;
	int res_v;

	mlx_get_screen_size(all->win->mlx, &res_h, &res_v);
	all->prms->res_v = (all->prms->res_v > res_v) ? res_v : all->prms->res_v;
	all->prms->res_h = (all->prms->res_h > res_h) ? res_h : all->prms->res_h;
	return (0);
}
