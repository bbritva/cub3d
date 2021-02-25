/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:11:28 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/25 15:44:49 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void 		get_shot(t_all *all)
{
	int		fd;
	int 	size;

	if ((fd = open("screenshot.txt", O_CREAT | O_WRONLY | O_APPEND | O_TRUNC,
				0777)) > 0)
	{
		ft_putstr("open OK\n");
		size = 54 + (all->prms->res_h * all->prms->res_v * all->win->bpp);
		write(fd, "BM", 2);
		write(fd, &size, 4);
		close(fd);
	}

	(void) all;
	ft_putstr("get_shot\n");
}