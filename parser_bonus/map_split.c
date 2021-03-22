/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 21:21:24 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/22 11:29:43 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static size_t	map_calcsize(char *s, char c)
{
	size_t result;

	result = 1;
	if (!s)
		return (0);
	if (*s == 0)
		return (0);
	while (*s)
	{
		if (*s == c)
			result++;
		s++;
	}
	return (result);
}

static size_t	arr_wide(const char *s, char c)
{
	size_t i;
	size_t len;
	size_t cur_len;

	i = 0;
	while (s[i])
	{
		cur_len = 0;
		while (s[i + cur_len] && s[i + cur_len] != c)
			cur_len++;
		len = (cur_len > len) ? cur_len : len;
		i += cur_len + 1;
	}
	return (++len);
}

static void		ft_freeresult(char **res, size_t count)
{
	while (count > 0)
		free(res[count--]);
	free(res);
}

static void		ft_fill(char **res, char *str, size_t size, size_t wide)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < size)
		if ((res[i] = (char *)ft_calloc(wide, sizeof(char))))
		{
			j = 0;
			while (*str && *str != '\n')
				res[i][j++] = *str++;
			i++;
			str += 1;
		}
		else
		{
			ft_freeresult(res, i);
			break ;
		}
}

char			**map_split(char const *s, char c)
{
	size_t	res_size;
	char	**result;
	size_t	wide;

	if (s == NULL)
		return (NULL);
	res_size = map_calcsize((char *)s, c);
	wide = arr_wide(s, c);
	result = (char **)ft_calloc((res_size + 1), sizeof(char *));
	if (result)
		ft_fill(result, (char *)s, res_size, wide);
	return (result);
}
