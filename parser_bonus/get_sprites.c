/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:50:14 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/29 12:08:20 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (ft_strchr("234", map[i][j]))
				size++;
			j++;
		}
		i++;
	}
	return (size);
}

t_sprite	*get_sprite(int j, int i, char type)
{
	t_sprite	*spr;

	if ((spr = (t_sprite *)ft_calloc(1, sizeof(t_sprite))))
	{
		spr->pos_x = (double)j + 0.5;
		spr->pos_y = (double)i + 0.5;
		spr->dist = 0;
		spr->angle = 0;
		spr->status_mask = (type == '2') ? Z_ALIVE : 0;
		spr->status_mask = (type == '3') ? (spr->status_mask | Z_BARREL) :
			spr->status_mask;
		spr->status_mask = (type == '4') ? (spr->status_mask | Z_DOOR) :
			spr->status_mask;
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
				if (ft_strchr("234", prms->map[i][j]) &&
					!(prms->sprites[k++] = get_sprite(j, i, prms->map[i][j])))
					return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}
