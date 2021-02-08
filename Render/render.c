/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/08 14:41:16 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

void		my_pixel_put(t_win *win, int x, int y, unsigned int color)
{
	char    *dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	ctoi(t_color color)
{
	return(color.red << 16 | color.green << 8 | color.blue);
}

void 		draw_fc(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (i < all->prms->res_v / 2)
	{
		j = 0;
		while (j < all->prms->res_h)
			my_pixel_put(all->win, j++, i, ctoi(all->prms->ceil_color));
		i++;
	}
	while (i < all->prms->res_v)
	{
		j = 0;
		while (j < all->prms->res_h)
			my_pixel_put(all->win, j++, i, ctoi(all->prms->floor_color));
		i++;
	}
}

void 		draw_line(t_all *all, int x_pos, int h)
{
	int i;

	if (h > all->prms->res_v)
		h = all->prms->res_v;
	i = (all->prms->res_v - h) / 2;
	while (i < (all->prms->res_v + h) / 2)
		my_pixel_put(all->win, x_pos, i++, 0x00007864);
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

int		get_height(t_all *all, double angle)
{
	t_player	p;
	int			h;
	double 		k;


	p = all->plr;
	while (all->prms->map[(int) (p.pos_y / SCALE)][(int) (p.pos_x / SCALE)]
	!= '1' && all->prms->map[(int) (p.pos_y / SCALE)][(int) (p.pos_x / SCALE)])
	{
		p.pos_x += 0.05f * cos(angle);
		p.pos_y -= 0.05f * sin(angle);
	}
	p.pos_x -= all->plr.pos_x;
	p.pos_y -= all->plr.pos_y;
	k = cos(angle - all->plr.ang_h);
	h = (int) (250 * SCALE / (sqrt((p.pos_x * p.pos_x) + (p.pos_y * p.pos_y)) *
			k));
	return (h);
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

int			key_press(int keycode, t_all *all)
{
	if (keycode == 13)
		all->win->move_mask = all->win->move_mask | FORWARD;
	if (keycode == 0)
		all->win->move_mask = all->win->move_mask | MV_LEFT;
	if (keycode == 1)
		all->win->move_mask = all->win->move_mask | BACKWARD;
	if (keycode == 2)
		all->win->move_mask = all->win->move_mask | MV_RIGHT;
	if (keycode == 124)
		all->win->move_mask = all->win->move_mask | RT_LEFT;
	if (keycode == 123)
		all->win->move_mask = all->win->move_mask | RT_RIGHT;
	return (0);
}

int			key_release(int keycode, t_all *all)
{
	if (keycode == 13)
		all->win->move_mask = all->win->move_mask & ~FORWARD;
	if (keycode == 0)
		all->win->move_mask = all->win->move_mask & ~MV_LEFT;
	if (keycode == 1)
		all->win->move_mask = all->win->move_mask & ~BACKWARD;
	if (keycode == 2)
		all->win->move_mask = all->win->move_mask & ~MV_RIGHT;
	if (keycode == 124)
		all->win->move_mask = all->win->move_mask & ~RT_LEFT;
	if (keycode == 123)
		all->win->move_mask = all->win->move_mask & ~RT_RIGHT;
	return (0);
}

int             key_hook(int keycode, t_win *win)
{
	printf("hooked key = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_image(win->mlx, win->img);
		mlx_destroy_window(win->mlx, win->win);
	}
	return (0);
}



int			mouse_hook(int button, int x, int y, t_win *win)
{
	(void) win;
	ft_putstr("Hello from mouse_hook!\n");
	ft_putnbr_fd(x, 1);
	ft_putstr("\n");
	ft_putnbr_fd(y, 1);
	ft_putstr("\n");
	ft_putnbr_fd(button, 1);
	ft_putstr("\n");
	return (0);
}

int			mouse_move_hook(int x, int y, t_win *win)
{
	(void) win;
	ft_putstr("Mouse_moved!\n");
	ft_putnbr_fd(x, 1);
	ft_putstr("\n");
	ft_putnbr_fd(y, 1);
	ft_putstr("\n");
	return (0);
}

int			move_fwd(t_all *all)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;

	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y - SPEED * sin(all->plr.ang_h)) / SCALE);
	j_new = (int)((all->plr.pos_x + SPEED * cos(all->plr.ang_h)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y -= SPEED * sin(all->plr.ang_h);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x += SPEED * cos(all->plr.ang_h);
	return (0);
}

int			move_bwd(t_all *all)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;

	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y + SPEED * sin(all->plr.ang_h)) / SCALE);
	j_new = (int)((all->plr.pos_x - SPEED * cos(all->plr.ang_h)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y += SPEED * sin(all->plr.ang_h);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x -= SPEED * cos(all->plr.ang_h);
	return (0);
}

int			move_left(t_all *all)
{
	int		i_cur;
	int		j_cur;
	int		i_new;
	int		j_new;
	double	ang;

	ang = all->plr.ang_h + M_PI_2;
	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y - SPEED * sin(ang)) / SCALE);
	j_new = (int)((all->plr.pos_x + SPEED * cos(ang)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y -= SPEED * sin(ang);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x += SPEED * cos(ang);
	return (0);
}

int			move_right(t_all *all)
{
	int		i_cur;
	int		j_cur;
	int		i_new;
	int		j_new;
	double	ang;

	ang = all->plr.ang_h - M_PI_2;
	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y - SPEED * sin(ang)) / SCALE);
	j_new = (int)((all->plr.pos_x + SPEED * cos(ang)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y -= SPEED * sin(ang);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x += SPEED * cos(ang);
	return (0);
}

int			render_next_frame(t_all *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	if (all->win->move_mask & FORWARD)
		move_fwd(all);
	if (all->win->move_mask & MV_LEFT)
		move_left(all);
	if (all->win->move_mask & BACKWARD)
		move_bwd(all);
	if (all->win->move_mask & MV_RIGHT)
		move_right(all);
	if (all->win->move_mask & RT_LEFT)
		all->plr.ang_h -= 0.06f;
	if (all->win->move_mask & RT_RIGHT)
		all->plr.ang_h += 0.06f;
	all->plr.ang_h -= (all->plr.ang_h > M_PI * 2)	? M_PI * 2 : 0;
	all->plr.ang_h += (all->plr.ang_h < 0) ? M_PI * 2 : 0;
	create_img(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	return (1);
}

void		render(t_all *all)
{
	if ((all->win = (t_win *)malloc(sizeof(t_win))))
	{
		all->win->mlx = mlx_init();
		all->win->win = mlx_new_window(all->win->mlx, all->prms->res_h,
								 all->prms->res_v, "cub3d");
		create_img(all);
		all->win->move_mask = 0;
		mlx_key_hook(all->win->win, key_hook, all->win);
//		mlx_mouse_hook(win->win, mouse_hook, win);
//		mlx_hook(win->win, 6, 1L << 6, mouse_move_hook, win);
		mlx_hook(all->win->win, 2, 1L << 0, key_press, all);
		mlx_hook(all->win->win, 3, 1L << 1, key_release, all);
		mlx_loop_hook(all->win->mlx, render_next_frame, all);
		mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
		mlx_loop(all->win->mlx);
//		free(all->win);
	}
}

