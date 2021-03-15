/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:40:19 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/15 15:49:48 by grvelva          ###   ########.fr       */
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
	mlx_string_put(all->win->mlx, all->win->win, 50, 50,
				   0x360000, ft_itoa(all->prms->plr.health));
	if (all->prms->plr.health <= 0)
	{
		mlx_string_put(all->win->mlx, all->win->win, 550, 300,
					   0x360000, "YOU DIED");
		mlx_string_put(all->win->mlx, all->win->win, 550, 320,
					   0x360000, "Press ESC to exit the game");
	}
	return (1);
}

int			key_hook(int key, t_all *all)
{
	if (key == 3)
		all->prms->plr.health -= 20;
	return (1);
}

int			my_exit(t_all *all)
{
	(void)all;
	exit(0);
}
