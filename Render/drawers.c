/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:53:07 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/09 11:28:16 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void 		draw_fc(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (i < all->prms->res_v / 2)
	{
		j = 0;
		while (j < all->prms->res_h)
			my_pixel_put(all->win, j++, i, all->prms->ceil_color);
		i++;
	}
	while (i < all->prms->res_v)
	{
		j = 0;
		while (j < all->prms->res_h)
			my_pixel_put(all->win, j++, i, all->prms->floor_color);
		i++;
	}
}

void 		draw_line(t_all *all, int x_pos, int h)
{
	int i;
	int color;

	if (h & NORTH)
	{
		color = 0x000000FF;
		h = h & ~(NORTH);
	}
	if (h & SOUTH)
	{
		color = 0x00FF0000;
		h = h & ~(SOUTH);
	}
	if (h & WEST)
	{
		color = 0x0000ff00;
		h = h & ~(WEST);
	}
	if (h & EAST)
	{
		color = 0x00557864;
		h = h & ~(EAST);
	}

	if (h > all->prms->res_v)
		h = all->prms->res_v;
	i = (all->prms->res_v - h) / 2;
	while (i < (all->prms->res_v + h) / 2)
		my_pixel_put(all->win, x_pos, i++, color);
}


void 		draw_map(t_win *win, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i/SCALE2])
	{
		j = 0;
		while (map[i/SCALE2][j/SCALE2])
		{
			if (map[i/SCALE2][j/SCALE2] == '1')
				my_pixel_put(win, j, i, 0x000000FF);
			if (map[i/SCALE2][j/SCALE2] == '0')
				my_pixel_put(win, j, i, 0x00FF0000);
			if (map[i/SCALE2][j/SCALE2] == '2')
				my_pixel_put(win, j, i, 0x0000FF00);
			if (ft_strchr("NSEW", map[i/SCALE2][j/SCALE2]))
				my_pixel_put(win, j, i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void		draw_player(t_all *all)
{
	t_player	p;
	int 		i;

	i = 0;
	p = all->plr;
	p.pos_x *= SCALE2;
	p.pos_y *= SCALE2;
	while (i < 10)
	{
		p.pos_x += cos(p.ang_h);
		p.pos_y -= sin(p.ang_h);
		my_pixel_put(all->win, (int) p.pos_x, (int) p.pos_y, 0x00FFFFFF);
		i++;
	}
}

void		draw_player_on_map(t_all *all)
{
	t_player	p;
	int 		x;
	int 		y;
	int			a;
	int 		b;

	p = all->plr;
	p.pos_y *= SCALE2;
	p.pos_x *= SCALE2;
	x = p.pos_x - SCALE2;
	while (x < p.pos_x + SCALE2)
	{
		y = p.pos_y - SCALE2;
		while (y < p.pos_y + SCALE2)
		{
			a = SCALE2 * SCALE2 / 8;
			b = (p.pos_x - x) * (p.pos_x - x) +	(p.pos_y - y) * (p.pos_y - y);
			if (b < a)
				my_pixel_put(all->win, x, y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}

void 		draw_view(t_all *all)
{
	int		i;
	double	angle;

	i = 0;
	while (i < all->prms->res_h)
	{
		angle = all->plr.ang_h + M_PI / 6 - i * (M_PI / (3 *
														 all->prms->res_h));
		(angle < 0) ? angle += 2 * M_PI : angle;
		(angle > 2 * M_PI) ? angle -= 2 * M_PI : angle;
		draw_line(all, i, get_height2(all, angle));
		i += 1;
	}

}

int			create_img(t_all *all)
{
	all->win->img = mlx_new_image(all->win->mlx, all->prms->res_h,
								  all->prms->res_v);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
									   &all->win->line_l, &all->win->en);
	draw_fc(all);
	draw_view(all);
	draw_map(all->win, all->prms->map);
	draw_player_on_map(all);
	draw_player(all);
	return (0);
}
