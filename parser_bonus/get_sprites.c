/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:50:14 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 12:34:06 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * BONUS
 */
#include "../includes_bonus/cub3d.h"

int			get_spr_count(char **map)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	i = 0;
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("2", map[i][j]))
				size++;
			j++;
		}
		i++;
	}
	return (size);
}

t_sprite	*get_sprite(int j, int i)
{
	t_sprite	*spr;

	if ((spr = (t_sprite *)ft_calloc(1, sizeof(t_sprite))))
	{
		spr->pos_x = (double)j + 0.5;
		spr->pos_y = (double)i + 0.5;
		spr->dist = 0;
		spr->angle = 0;
		spr->status_mask = Z_ALIVE;
	}
	return (spr);
}

int			get_sprites(t_params *prms)
{
	int	i;
	int	j;
	int	k;

	if ((prms->sprites = (t_sprite **)ft_calloc(get_spr_count(prms->map) + 1,
												sizeof(t_sprite *))))
	{
		i = 0;
		k = 0;
		while (prms->map[i] != 0)
		{
			j = 0;
			while (prms->map[i][j])
			{
				if (ft_strchr("2", prms->map[i][j]) &&
					!(prms->sprites[k++] = get_sprite(j, i)))
					return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}