/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 11:27:36 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 11:34:28 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void		sort_sprites(t_sprite **sprites)
{
	int			i;
	int			j;
	t_sprite	*temp;

	i = 0;
	if (!sprites || !sprites[0])
		return ;
	while (sprites[i + 1])
	{
		j = i;
		while (sprites[j + 1])
		{
			if (sprites[j]->dist > sprites[j + 1]->dist)
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

void			prepare_sprites(t_all *all)
{
	int			i;

	i = 0;
	while (all->prms->sprites[i])
	{
		set_spr_prms(all->prms->sprites[i++], all->prms->plr);
	}
	sort_sprites(all->prms->sprites);
}
