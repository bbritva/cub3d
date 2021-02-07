/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:09:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/07 15:36:09 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# define SCALE 1
# define SCALE2 10
# define SPEED 0.05f
# define FORWARD 32
# define BACKWARD 16
# define MV_LEFT 8
# define MV_RIGHT 4
# define RT_LEFT 2
# define RT_RIGHT 1

typedef struct	s_win //структура для окна
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
	unsigned int	move_mask;
}					t_win;

void		my_pixel_put(t_win *win, int x, int y, unsigned int	color);

#endif
