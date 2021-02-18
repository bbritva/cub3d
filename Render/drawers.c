/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:53:07 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/18 14:25:47 by grvelva          ###   ########.fr       */
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

	color = 0x00FFFFFF;
	if (h & NORTH)
		color = 0x000000FF;
	if (h & SOUTH)
		color = 0x00FF0000;
	if (h & WEST)
		color = 0x0000FF00;
	if (h & EAST)
		color = 0x00999999;
	h = h & ~(0b1111 << 12);
	if (h > all->prms->res_v)
		h = all->prms->res_v;
	i = (all->prms->res_v - h) / 2;
	while (i < (all->prms->res_v + h) / 2)
		my_pixel_put(all->win, x_pos, i++, color);
}

int 		get_pxl(t_tex *tex, int i, int h, int x_coor)
{
	char    *src;
	int		color;
	int 	y;
	int 	x;

	y = tex->h_tex * i / h;
	x = tex->w_tex * x_coor / 255;
	src = tex->addr + (y * tex->line_l + x * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

void 		draw_txtr_line(t_all *all, int x_pos, int h, int center)
{
	int i;
	int x_coor;
	t_tex *tex;
	int color;

	tex = all->win->sprite;
	if (h & NORTH)
		tex = all->win->north;
	if (h & SOUTH)
		tex = all->win->south;
	if (h & WEST)
		tex = all->win->west;
	if (h & EAST)
		tex = all->win->east;
	h = h & ~(0b1111 << 26);
	x_coor = h >> 16;
	h = h & ~(0b11111111 << 16);
//	if (h > all->prms->res_v)
//		h = all->prms->res_v;
	i = 0;
	while (i < h)
	{

		if ((all->prms->res_v - h) / 2 + i  + center > -1 && (all->prms->res_v
		- h) / 2 + i  + center < all->prms->res_v && (color = get_pxl(tex, i, h,
													  x_coor)) > 0)
		{
			my_pixel_put(all->win, x_pos, (all->prms->res_v - h) / 2
			+ i + center, color);
		}
		i++;
	}
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
	x = (int) (p.pos_x - SCALE2);
	while (x < p.pos_x + SCALE2)
	{
		y = (int) (p.pos_y - SCALE2);
		while (y < p.pos_y + SCALE2)
		{
			a = (int) pow(SCALE2, 2) / 8;
			b = (int) (pow(p.pos_x - x, 2) + pow(p.pos_y - y, 2));
			if (b < a)
				my_pixel_put(all->win, x, y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}

void 		draw_walls(t_all *all)
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
		draw_txtr_line(all, i, get_height(all, angle), 0);
		i += 1;
	}

}

void 		sort_sprites(t_sprite **sprites)
{
	int			i;
	int			j;
	t_sprite	*temp;

	i = 0;
	while (sprites[i + 1])
	{
		j = i;
		while (sprites[j + 1])
		{
			if (sprites[j]->dist < sprites[j + 1]->dist)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}


}

void		prepare_sprites(t_all *all)
{
	int			i;
//	double		angle;

	i = 0;
	while (all->prms->sprites[i])
	{
		set_spr_prms(all->prms->sprites[i++], all->plr);
	}
	sort_sprites(all->prms->sprites);
}

void 		draw_sprites(t_all *all)
{
	int		i;
	int		j;
	int 	n;
	int 	x_coor;
	char 	isVisible;
	double	angle;
	int		size;

	i = 0;
	prepare_sprites(all);
	while (all->prms->sprites[i])
	{
		angle = all->plr.ang_h - all->prms->sprites[i]->angle;
		angle -= (angle > M_PI * 2)	? M_PI * 2 : 0;
		angle += (angle < 0) ? M_PI * 2 : 0;
		n = (int)((0.5 + sin(angle)) * all->prms->res_h);
		size = (int)(all->prms->res_v / (1.2 * all->prms->sprites[i]->dist));
		j = n - size / 2;
		while (j < n + size / 2)
		{
			isVisible = 0;
			if (get_wall_dist(all, all->prms->sprites[i]->angle) >
			all->prms->sprites[i]->dist)
				isVisible = 1;
			if (j > 0 && j < all->prms->res_h && (angle < (M_PI / 2) || angle
			> (3 * M_PI / 2)) && isVisible)
			{
				x_coor = (j - n + size / 2) * 255 / size;
				draw_txtr_line(all, j, size | x_coor << 16, 0);
			}
			j++;
		}
		i++;
	}

}

int			create_img(t_all *all)
{
	all->win->img = mlx_new_image(all->win->mlx, all->prms->res_h,
								  all->prms->res_v);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
									   &all->win->line_l, &all->win->en);
	draw_fc(all);
	draw_walls(all);
	draw_sprites(all);
	draw_map(all->win, all->prms->map);
	draw_player_on_map(all);
	draw_player(all);
	return (0);
}
