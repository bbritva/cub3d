/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:43:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:09:25 by grvelva          ###   ########.fr       */
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

# define BUFFER_SIZE 256

int		check_input(int fd, char **line);
int		get_next_line(int fd, char **line);
void	ft_putstr(char *str);
size_t	gnl_strlen(const char *str);
char	*gnl_strjoin(char *s1, char *s2);
int		has_buff_nl(char *buff);
char	*getline_from_buff(char *buff);
char	*buff_trim(char *buff, size_t len);
void	gnl_strlcpy(char *dest, const char *src, size_t size);
char	*init_buff(char *buff, int fd);

#endif
