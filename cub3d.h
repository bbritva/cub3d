/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:24:13 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/08 19:31:18 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# define BUFFER_SIZE 5
# define F_MISS_MSG "File name missing.\n"
# define M_ARGS_MSG "Too many arguments.\n"
# define NREAD_MSG "Cannot read file.\n"

typedef	struct
{
	unsigned int	flag;
	int				wide;
	int				precision;
	char			type;
	int				dbl_type;
	int				parsed_size;
}					t_frmt;

int		check_input(int fd, char **line);
int		get_next_line(int fd, char **line);
void	ft_putstr(char *str, int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		has_buff_nl(char *buff);
char	*getline_from_buff(char *buff);
int		stdin_read(char **line);
char	*buff_trim(char *buff, size_t len);
void	ft_strlcpy(char *dest, const char *src, size_t size);
char	*init_buff(char *buff, int fd);

#endif
