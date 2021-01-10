/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:43:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/09 11:09:43 by grvelva          ###   ########.fr       */
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

# define BUFFER_SIZE 32

int		check_input(int fd, char **line);
int		get_next_line(int fd, char **line);
void	ft_putstr(char *str);
size_t	ft_strlen(const char *str);
char	*gnl_strjoin(char *s1, char *s2);
int		has_buff_nl(char *buff);
char	*getline_from_buff(char *buff);
int		stdin_read(char **line);
char	*buff_trim(char *buff, size_t len);
void	gnl_strlcpy(char *dest, const char *src, size_t size);
char	*init_buff(char *buff, int fd);

#endif
