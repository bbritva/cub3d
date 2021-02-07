/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:24:13 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/07 15:38:43 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Parser/parser.h"
# include "./Render/render.h"
# include "./libft/libft.h"
# include "./GNL/get_next_line.h"
# include <mlx.h>

typedef struct
{
	t_player 		*plr;
	t_params		*prms;
	t_win			*win;
}					t_all;

void 				render(t_all	*all);
int					parser(char *f_name, t_all *all);
void				show_parse_res(t_all *all);
int					map_parser(int fd, t_all *all, char **line);
int					get_player(t_all *all);
void				ft_putstr(char *str);
int					get_height2(t_all *all, double angle);
int					is_wall(t_all *all, t_player p, double angle, char hv);





#endif
