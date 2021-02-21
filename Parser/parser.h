/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:04:51 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/21 10:12:55 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "../libft/libft.h"
# include "../GNL/get_next_line.h"

# define F_MISS_MSG "File name missing.\n"
# define M_ARGS_MSG "Wrong arguments.\n"
# define NREAD_MSG "Cannot read file.\n"

typedef struct
{
	double			pos_x;
	double			pos_y;
	double			ang_h;
	double			angle_v;
}					t_player;

typedef struct		s_sprite
{
	int 			pos_x;
	int 			pos_y;
	double			dist;
	double			angle;
}					t_sprite;

typedef	struct
{
	int				res_v;
	int				res_h;
	char 			*north;
	char 			*south;
	char 			*west;
	char 			*east;
	char 			*sprite;
	int				floor_color;
	int				ceil_color;
	int				i;
	char 			**map;
	t_sprite		**sprites;
	t_player		plr;
	double			*dists;
}					t_params;

int					get_color(char *line, int color);
int					is_map_line(char *line);
t_params			*param_parser(int fd, t_params *params, char **line);
char				**map_split(char const *s, char c);
int					skip_spaces(const char *str, int i);
void				show_parse_res(t_params *prms);
int					map_parser(int fd, t_params *prms, char **line);
int					get_player(t_params *prms);
int				 	get_sprites(t_params *prms);





#endif
