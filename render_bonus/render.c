/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 12:21:40 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	*tex_init(t_all *all, char *path)
{
	t_tex *tex;

	if ((tex = ft_calloc(1, sizeof(t_tex))))
		if ((tex->img = mlx_xpm_file_to_image(all->win->mlx, path,
										&tex->w_tex, &tex->h_tex)))
		{
			tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_l,
				&tex->en);
			return (tex);
		}
	return (NULL);
}

static void	start_game(t_all *all)
{
	system("afplay resources/sounds/combat0.mp3 &");
	mlx_hook(all->win->win, 2, 1L << 0, key_press, all);
	mlx_hook(all->win->win, 17, 1L << 17, my_exit, all);
	mlx_hook(all->win->win, 3, 1L << 1, key_release, all);
	mlx_hook(all->win->win, 6, 1L << 6, mouse_move_hook, all);
	mlx_loop_hook(all->win->mlx, render_next_frame, all);
	mlx_loop(all->win->mlx);
}

static int	init_window(t_all *all, int argc)
{
	if ((all->win = (t_win *)ft_calloc(1, sizeof(t_win))) &&
		(all->win->mlx = mlx_init()))
	{
		if (argc == 2)
			crop_resolution(all);
		if ((all->win->win = mlx_new_window(all->win->mlx, all->prms->res_h,
				all->prms->res_v, "cub3d")) &&
			(all->win->north = tex_init(all, all->prms->north)) &&
			(all->win->south = tex_init(all, all->prms->south)) &&
			(all->win->west = tex_init(all, all->prms->west)) &&
			(all->win->east = tex_init(all, all->prms->east)) &&
			(all->win->sprite = tex_init(all, all->prms->sprite)) &&
			(all->win->sky = tex_init(all, SKY_PATH)) &&
			(all->win->floor = tex_init(all, FLOOR_PATH)) &&
			(all->win->gun = tex_init(all, GUN_PATH)) &&
			(all->win->gun2 = tex_init(all, GUN2_PATH)) &&
			(all->win->sprite2 = tex_init(all, SPRITE2_PATH)) &&
			(all->win->door = tex_init(all, DOOR_PATH)))
			return (1);
	}
	return (0);
}

void		render(t_params *prms, int argc)
{
	t_all *all;

	if ((all = (t_all *)ft_calloc(1, sizeof(t_all))))
	{
		all->prms = prms;
		if (init_window(all, argc))
		{
			create_img(all);
			all->win->move_mask = 0;
			if (argc == 2)
				start_game(all);
			else
				get_shot(all);
			free_window(all);
			free(all->win);
		}
		else
		{
			ft_putstr(INIT_ERR_MSG);
			free_window(all);
		}
	}
	else
		ft_putstr(ALLOC_ERR_MSG);
}

int			my_exit(t_all *all)
{
	(void)all;
	system("killall afplay");
	exit(0);
}
