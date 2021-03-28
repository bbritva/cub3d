/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:40:05 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 12:18:37 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void		draw_circle(t_all *data, int x_c, int y_c, int r)
{
	int x;
	int y;
	int delta;
	int error;

	x = 0;
	y = r;
	delta = 1 - 2 * r;
	while (y >= 0)
	{
		my_pixel_put(data->win, x_c + x, y_c + y, 0xFFFFFF);
		my_pixel_put(data->win, x_c + x, y_c - y, 0xFFFFFF);
		my_pixel_put(data->win, x_c - x, y_c + y, 0xFFFFFF);
		my_pixel_put(data->win, x_c - x, y_c - y, 0xFFFFFF);
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
			delta += 2 * ++x + 1;
		else if ((delta > 0) && (error > 0))
			delta -= 2 * --y + 1;
		else
			delta += 2 * (++x - --y);
	}
}

static void		draw_cross(t_all *data, int x_c, int y_c, int r)
{
	int x;
	int y;

	x = x_c - r - 5;
	while (x < x_c - r + 5)
		my_pixel_put(data->win, x++, y_c, 0xFFFFFF);
	x = x_c + r - 5;
	while (x < x_c + r + 5)
		my_pixel_put(data->win, x++, y_c, 0xFFFFFF);
	y = y_c - r - 5;
	while (y < y_c - r + 5)
		my_pixel_put(data->win, x_c, y++, 0xFFFFFF);
	y = y_c + r - 5;
	while (y < y_c + r + 5)
		my_pixel_put(data->win, x_c, y++, 0xFFFFFF);
}

static void		draw_underlay(t_all *all)
{
	int x;
	int y;

	x = 5;
	y = all->prms->res_v - 5;
	while (x < 70)
		my_pixel_put(all->win, x++, y, 0xFFFFFF);
	while (all->prms->res_v - y < 300)
		my_pixel_put(all->win, x, y--, 0xFFFFFF);
	while (x > 5)
		my_pixel_put(all->win, x--, y, 0xFFFFFF);
	while (all->prms->res_v - y > 5)
		my_pixel_put(all->win, x, y++, 0xFFFFFF);
}

static void		draw_livebar(t_all *all)
{
	int x;
	int y;

	y = all->prms->res_v - 6;
	while (all->prms->res_v - y < 3 * all->prms->plr.health)
	{
		x = 6;
		while (x < 70)
			my_pixel_put(all->win, x++, y, 0x8B0000);
		y--;
	}
}

void			draw_hud(t_all *all)
{
	int x_c;
	int y_c;

	draw_underlay(all);
	draw_livebar(all);
	draw_minimap(all);
	x_c = all->prms->res_h / 2;
	y_c = all->prms->res_v / 2;
	draw_circle(all, x_c, y_c, 20);
	draw_cross(all, x_c, y_c, 20);
}
