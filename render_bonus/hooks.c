/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:40:19 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 16:43:14 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * BONUS
 */
#include "../includes_bonus/cub3d.h"

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
	if (keycode == 53)
		all->win->move_mask = all->win->move_mask | ESC;
	if (keycode == 256)
		shoot(all);
	ft_putnbr_fd(keycode, 1);
	ft_putstr("\n");
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

int			render_next_frame(t_all *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	move_plr(all);
	move_zombies(all);
	create_img(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	if (all->prms->plr.health <= 0)
	{
		mlx_string_put(all->win->mlx, all->win->win, 550, 300,
					   0x8B0000, "YOU DIED");
		mlx_string_put(all->win->mlx, all->win->win, 550, 320,
					   0x8B0000, "Press ESC to exit the game");
	}
	return (1);
}

int			mouse_move_hook(int x, int y, t_all *all)
{
	(void) y;
	mlx_mouse_hide();
	all->prms->plr.ang_h += 0.02f * (640 - x) / 10;
	mlx_mouse_move(all->win->win, 640, 0);
	return (0);
}

int			my_exit(t_all *all)
{
	(void)all;
	system("killall afplay");
	exit(0);
}

int 		shoot(t_all *all)
{
	int		i;
	double	angle;

	(void) all;
	i = 0;
	while (all->prms->sprites[i] && all->prms->sprites[i]->dist < SHOOT_DIST)
	{
		angle = all->prms->plr.ang_h - all->prms->sprites[i]->angle;
		angle -= (angle > M_PI * 2) ? M_PI * 2 : 0;
		angle += (angle < 0) ? M_PI * 2 : 0;
		if (fabs(angle) < M_PI_4 / 5)
		{
			all->prms->sprites[i]->status_mask =
					all->prms->sprites[i]->status_mask & ~(Z_ALIVE);
		}
		i++;
	}
	ft_putstr("shoot!!!\n");
	return (0);
}
