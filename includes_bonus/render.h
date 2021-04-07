/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:09:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/04/04 11:23:08 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include "../minilibx_mms/mlx.h"
# include "cub3d.h"
# define INIT_ERR_MSG "Error\nIMG initialization error (wrong texture path)\n"
# define SKY_PATH "./resources/textures/sky.xpm"
# define DOOR_PATH "./resources/textures/door.xpm"
# define FLOOR_PATH "./resources/textures/floor.xpm"
# define GUN_PATH "./resources/textures/Shotgun.xpm"
# define GUN2_PATH "./resources/textures/Shotgun2.xpm"
# define SPRITE2_PATH "./resources/textures/barrel.xpm"
# define SCALE 1
# define SPEED 0.095f
# define SPEED_Z 0.08f
# define ESC 1 << 6
# define IS_BITTEN 1 << 7
# define IS_SHOOT 1 << 8
# define FORWARD 32
# define BACKWARD 16
# define MV_LEFT 8
# define MV_RIGHT 4
# define RT_LEFT 2
# define RT_RIGHT 1
# define D 0.1f
# define NORTH 1 << 26
# define SOUTH 1 << 27
# define WEST 1 << 28
# define EAST 1 << 29
# define BARREL 1 << 30
# define DOOR 1 << 31
# define SPOT_DIST 10
# define SHOOT_DIST 7

typedef struct		s_tex
{
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
	int				w_tex;
	int				h_tex;
}					t_tex;

typedef struct		s_win
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
	t_tex			*sprite2;
	t_tex			*door;
	t_tex			*sky;
	t_tex			*floor;
	t_tex			*gun;
	t_tex			*gun2;
}					t_win;

typedef struct		s_all
{
	t_params		*prms;
	t_win			*win;
}					t_all;

int					set_spr_prms(t_sprite *spr, t_player plr);
void				prepare_sprites(t_all *all);
void				my_pixel_put(t_win *win, int x, int y, unsigned int	color);
int					get_height(t_all *all, int i);
int					is_wall(t_all *all, t_player p, double angle, char hv);
int					key_press(int keycode, t_all *all);
int					key_release(int keycode, t_all *all);
int					render_next_frame(t_all *all);
int					create_img(t_all *all);
void				get_shot(t_all *all);
int					crop_resolution(t_all *all);
int					free_window(t_all *all);
void				draw_txtr_line(t_all *all, int x_pos, int h);
void				draw_sprites(t_all *all);
int					my_exit(t_all *all);
int					move_plr(t_all *all);
void				move_zombies(t_all *all);
int					shadow_color(int color, int h, int res_h);
int					mouse_move_hook(int x, int y, t_all *all);
void				draw_hud(t_all *all);
void				draw_minimap(t_all *all);
void				draw_sky(t_all *all);
void				draw_txtr_floor(t_all *all);
void				draw_gun(t_all *all);
void				draw_door(int size, t_sprite *spr, int n, t_all *all);
int					shoot(t_all *all);
void				move_doors(t_all *all);

#endif
