/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:48:23 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/01 17:03:00 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	free_tex(t_tex *tex, void *mlx)
{
	if (tex)
	{
		if (tex->img)
			mlx_destroy_image(mlx, tex->img);
		free(tex);
	}
	return (0);
}

int			free_window(t_all *all)
{
	if (all->win->north)
		free_tex(all->win->north, all->win->mlx);
	if (all->win->south)
		free_tex(all->win->south, all->win->mlx);
	if (all->win->west)
		free_tex(all->win->west, all->win->mlx);
	if (all->win->east)
		free_tex(all->win->east, all->win->mlx);
	if (all->win->sprite)
		free_tex(all->win->sprite, all->win->mlx);
	return (0);
}
