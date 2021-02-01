/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:09:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/01 11:49:44 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# define SCALE 20
# define SPEED 1
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
	t_params		*prms;
}					t_win;

void		my_pixel_put(t_win *win, int x, int y, unsigned int	color);
int			get_height2(t_win *win, double angle);


#endif
