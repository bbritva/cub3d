/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:43:11 by grvelva           #+#    #+#             */
/*   Updated: 2020/11/18 09:01:50 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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
