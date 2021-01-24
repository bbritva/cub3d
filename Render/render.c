/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/24 20:00:12 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char    *dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

void 		draw_map(t_win *win, char **map)
{
	int i;
	int j;
	int k = 20;

	i = 0;
	while (map[i/k])
	{
		j = 0;
		while (map[i/k][j/k])
		{
			if (map[i/k][j/k] == '1')
				my_mlx_pixel_put(win, j, i, 0x000000FF);
			if (map[i/k][j/k] == '0')
				my_mlx_pixel_put(win, j, i, 0x00FF0000);
			if (map[i/k][j/k] == '2')
				my_mlx_pixel_put(win, j, i, 0x0000FF00);
			if (ft_strchr("NSEW", map[i/k][j/k]))
				my_mlx_pixel_put(win, j, i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void		draw_player(t_win *win, t_params *params)
{
	int i;
	int j;
	t_player p;

	p = *(params->player);
	i = (int)(p.pos_y / SCALE);
	j = (int)(p.pos_x / SCALE);
	while (params->map[i][j] != '1')
	{
		p.pos_x += cos(p.angle_h);
		p.pos_y -= sin(p.angle_h);

		my_mlx_pixel_put(win, p.pos_x, p.pos_y, 0x00FFFFFF);
		i = (int)(p.pos_y / SCALE);
		j = (int)(p.pos_x / SCALE);
	}
}

int		create_img(t_params *params, t_win *win)
{
	win->img = mlx_new_image(win->mlx, params->res_h, params->res_v);
	win->addr = mlx_get_data_addr(win->img, &win->bpp,
								  &win->line_l, &win->en);
	draw_map(win, params->map);
	draw_player(win, params);
	return (0);
}

int			key_hook(int keycode, t_win *win)
{
	ft_putstr("Hello from key_hook!\n");
	ft_putnbr_fd(keycode, 1);
	ft_putstr("\n");
	if (keycode == 126 || keycode == 13)
		win->params->player->pos_y -= 0.5f;
	if (keycode == 0)
		win->params->player->pos_x -= 0.5f;
	if (keycode == 1 || keycode == 125)
		win->params->player->pos_y += 0.5f;
	if (keycode == 2)
		win->params->player->pos_x += 0.5f;
	if (keycode == 124)
		win->params->player->angle_h -= 0.03f;
	if (keycode == 123)
		win->params->player->angle_h += 0.03f;
	if (keycode == 53)
	{
		mlx_destroy_image(win->mlx, win->img);
		mlx_destroy_window(win->mlx, win->win);
	}
	return (0);
}

int			key_press(int keycode, t_win *win)
{
	if (keycode == 126 || keycode == 13)
		win->move_mask = win->move_mask | FORWARD;
	if (keycode == 0)
		win->move_mask = win->move_mask | MV_LEFT;
	if (keycode == 1 || keycode == 125)
		win->move_mask = win->move_mask | BACKWARD;
	if (keycode == 2)
		win->move_mask = win->move_mask | MV_RIGHT;
	if (keycode == 124)
		win->move_mask = win->move_mask | RT_LEFT;
	if (keycode == 123)
		win->move_mask = win->move_mask | RT_RIGHT;
	if (keycode == 53)
	{
		mlx_destroy_image(win->mlx, win->img);
		mlx_destroy_window(win->mlx, win->win);
	}
	return (0);
}

int			key_release(int keycode, t_win *win)
{
	if (keycode == 126 || keycode == 13)
		win->move_mask = win->move_mask - FORWARD;
	if (keycode == 0)
		win->move_mask = win->move_mask - MV_LEFT;
	if (keycode == 1 || keycode == 125)
		win->move_mask = win->move_mask - BACKWARD;
	if (keycode == 2)
		win->move_mask = win->move_mask - MV_RIGHT;
	if (keycode == 124)
		win->move_mask = win->move_mask - RT_LEFT;
	if (keycode == 123)
		win->move_mask = win->move_mask - RT_RIGHT;
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

int			move_fwd(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->params->player);
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y - sin(p.angle_h)) / SCALE);
	j_new = (int)((p.pos_x + cos(p.angle_h)) / SCALE);
	if (win->params->map[i_new][j_cur] != '1')
		win->params->player->pos_y -= sin(p.angle_h);
	if (win->params->map[i_cur][j_new] != '1')
		win->params->player->pos_x += cos(p.angle_h);
	return (0);
}

int			move_bwd(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->params->player);
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y + sin(p.angle_h))/ SCALE);
	j_new = (int)((p.pos_x - cos(p.angle_h)) / SCALE);
	if (win->params->map[i_new][j_cur] != '1')
		win->params->player->pos_y += sin(p.angle_h);
	if (win->params->map[i_cur][j_new] != '1')
		win->params->player->pos_x -= cos(p.angle_h);
	return (0);
}

int			move_left(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->params->player);
	p.angle_h += M_PI_2;
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y - sin(p.angle_h))/ SCALE);
	j_new = (int)((p.pos_x + cos(p.angle_h)) / SCALE);
	if (win->params->map[i_new][j_cur] != '1')
		win->params->player->pos_y -= sin(p.angle_h);
	if (win->params->map[i_cur][j_new] != '1')
		win->params->player->pos_x += cos(p.angle_h);
	return (0);
}

int			move_right(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->params->player);
	p.angle_h -= M_PI_2;
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y - sin(p.angle_h))/ SCALE);
	j_new = (int)((p.pos_x + cos(p.angle_h)) / SCALE);
	if (win->params->map[i_new][j_cur] != '1')
		win->params->player->pos_y -= sin(p.angle_h);
	if (win->params->map[i_cur][j_new] != '1')
		win->params->player->pos_x += cos(p.angle_h);
	return (0);
}

int			render_next_frame(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	if (win->move_mask & FORWARD)
		move_fwd(win);
	if (win->move_mask & MV_LEFT)
		move_left(win);
	if (win->move_mask & BACKWARD)
		move_bwd(win);
	if (win->move_mask & MV_RIGHT)
		move_right(win);
	if (win->move_mask & RT_LEFT)
		win->params->player->angle_h -= 0.03f;
	if (win->move_mask & RT_RIGHT)
		win->params->player->angle_h += 0.03f;
	create_img(win->params, win);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	return (1);
}

void		render(t_params	*params)
{
	t_win		*win;

	if ((win = (t_win *)malloc(sizeof(t_win))))
	{
		win->mlx = mlx_init();
		win->win = mlx_new_window(win->mlx, params->res_h, params->res_v,
								  "cub3d");
		create_img(params, win);
		win->params = params;
		win->move_mask = 0;
		mlx_key_hook(win->win, key_hook, win);
//		mlx_mouse_hook(win->win, mouse_hook, win);
//		mlx_hook(win->win, 6, 1L << 6, mouse_move_hook, win);
		mlx_hook(win->win, 2, 1L << 0, key_press, win);
		mlx_hook(win->win, 3, 1L << 1, key_release, win);
		mlx_loop_hook(win->mlx, render_next_frame, win);
		mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
		mlx_loop(win->mlx);
	}
}

