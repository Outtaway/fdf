/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 10:19:29 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/07 14:22:03 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*copy_loop(char *str, char *buff, int end)
{
	char	*temp;

	if (str)
	{
		temp = ft_strnew(ft_strlen(str) + end);
		if (!temp)
			return (NULL);
		ft_strcpy(temp, str);
		ft_strcat(temp, buff);
		free(str);
	}
	else
	{
		temp = ft_strnew(end);
		if (!temp)
			return (NULL);
		ft_strcpy(temp, buff);
	}
	return (temp);
}

int		get_next_line(const int fd, char **line, const int buff_size)
{
	static char	*str = NULL;
	int			end;
	char		buff[buff_size + 1];
	char		*slash;
	char		*temp;

	SHIT2;
	while (1)
	{
		if ((slash = ft_strchr(temp, '\n')) != NULL)
		{
			*line = ft_strsub(temp, 0, ft_strlen(temp) - ft_strlen(slash));
			SHIT4;
		}
		if ((end = read(fd, buff, buff_size)) <= 0)
		{
			if (temp && temp[0] && (end = 1))
				*line = ft_strsub(temp, 0, ft_strlen(temp));
			break ;
		}
		buff[end] = '\0';
		temp = copy_loop(temp, buff, end);
	}
	ft_strdel(&temp);
	return (end);
}
