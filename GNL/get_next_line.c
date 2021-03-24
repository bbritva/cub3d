/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:50:47 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:09:25 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_input(int fd, char **line)
{
	char	test_buff[1];

	if (fd < 0)
		return (0);
	if ((read(fd, test_buff, 0)) < 0)
		return (0);
	if (!line)
		return (0);
	return (1);
}

int		has_buff_nl(char *buff)
{
	int i;

	if (buff)
	{
		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*getline_from_buff(char *buff)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = 0;
	while (buff[len] != '\n' && buff[len] != 0)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res)
	{
		i = 0;
		while (i < len)
		{
			res[i] = buff[i];
			i++;
		}
		res[i] = 0;
	}
	return (res);
}

int		get_next_line(int fd, char **line)
{
	static char	*buff = NULL;

	if (!check_input(fd, line))
		return (-1);
	if (!(buff = init_buff(buff, fd)))
		return (-1);
	if (has_buff_nl(buff))
	{
		if ((*line = getline_from_buff(buff)))
			if ((buff = buff_trim(buff, gnl_strlen(*line) + 1)))
				return (1);
		free(buff);
		return (-1);
	}
	*line = gnl_strjoin(buff, "\0");
	buff = NULL;
	return (0);
}

char	*init_buff(char *buff, int fd)
{
	char	*buff1;
	int		ret;

	buff1 = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff1)
	{
		while (!has_buff_nl(buff) && ((ret = read(fd, buff1, BUFFER_SIZE)) > 0))
		{
			buff1[ret] = 0;
			buff = gnl_strjoin(buff, buff1);
		}
		if (!buff)
			buff = gnl_strjoin(buff, "\0");
		free(buff1);
		buff1 = NULL;
		return (buff);
	}
	return (NULL);
}
