/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:05:44 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/06 13:51:03 by grvelva          ###   ########.fr       */
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
# include "../GNL/get_next_line.h"
# include "../libft/libft.h"

# define F_MISS_MSG "File name missing.\n"
# define M_ARGS_MSG "Too many arguments.\n"
# define NREAD_MSG "Cannot read file.\n"

typedef struct
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
}					t_color;

typedef struct
{
	double			pos_x;
	double			pos_y;
	double			ang_h;
	double			angle_v;
}					t_player;

typedef	struct
{
	int				res_v;
	int				res_h;
	char 			*north;
	char 			*south;
	char 			*west;
	char 			*east;
	char 			*sprite;
	t_color			floor_color;
	t_color			ceil_color;
	t_player		*plr;
	char 			**map;
}					t_params;

t_params			*parser(char *f_name);
t_color				get_color(char *line, t_color color);
int					is_map_line(char *line);
t_params			*param_parser(int fd, t_params *params, char **line);
t_params			*map_parser(int fd, t_params *params, char **line);
char				**map_split(char const *s, char c);

#endif
