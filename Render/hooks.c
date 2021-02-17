/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:40:19 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/16 19:12:52 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

//int			mouse_hook(int button, int x, int y, t_win *win)
//{
//	(void) win;
//	ft_putstr("Hello from mouse_hook!\n");
//	ft_putnbr_fd(x, 1);
//	ft_putstr("\n");
//	ft_putnbr_fd(y, 1);
//	ft_putstr("\n");
//	ft_putnbr_fd(button, 1);
//	ft_putstr("\n");
//	return (0);
//}
//
//int			mouse_move_hook(int x, int y, t_win *win)
//{
//	(void) win;
//	ft_putstr("Mouse_moved!\n");
//	ft_putnbr_fd(x, 1);
//	ft_putstr("\n");
//	ft_putnbr_fd(y, 1);
//	ft_putstr("\n");
//	return (0);
//}

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
	if (all->win->move_mask & ESC)
	{
		mlx_clear_window(all->win->mlx, all->win->win);
		mlx_destroy_window(all->win->mlx, all->win->win);
		exit(0);
	}
	all->plr.ang_h -= (all->plr.ang_h > M_PI * 2)	? M_PI * 2 : 0;
	all->plr.ang_h += (all->plr.ang_h < 0) ? M_PI * 2 : 0;
	create_img(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	return (1);
}