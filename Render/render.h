/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:09:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/10 23:08:26 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include <mlx.h>
# include "../cub3d.h"
# define SCALE 1
# define SCALE2 10
# define SPEED 0.05f
# define ESC 64
# define FORWARD 32
# define BACKWARD 16
# define MV_LEFT 8
# define MV_RIGHT 4
# define RT_LEFT 2
# define RT_RIGHT 1
# define D 0.2f
# define NORTH 1 << 26
# define SOUTH 1 << 27
# define WEST 1 << 28
# define EAST 1 << 29

typedef struct	s_tex //структура для окна
{
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
	int 			w_tex;
	int 			h_tex;
}					t_tex;

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
	t_tex			*north;
	t_tex			*south;
	t_tex			*west;
	t_tex			*east;
	t_tex			*sprite;
}					t_win;






#endif
