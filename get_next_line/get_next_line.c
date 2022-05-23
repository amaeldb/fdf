/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:11:08 by ade-beta          #+#    #+#             */
/*   Updated: 2021/12/15 14:10:49 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*saveret(char **save)
{
	char	*temp;
	char	*ret;

	temp = *save;
	*save = gnl_strdup(gnl_strchr(*save, '\n') + 1);
	ret = gnl_strdup(temp);
	free(temp);
	ret[gnl_strlen(ret) - gnl_strlen(*save)] = '\0';
	temp = gnl_strdup(ret);
	free(ret);
	return (temp);
}

char	*gnlret(int i, char **save)
{
	char	*temp;

	if (gnl_strchr(*save, '\n'))
		return (saveret(&*save));
	else if (i == 0 && gnl_strlen(*save) > 0)
	{
		temp = gnl_strdup(*save);
		free(*save);
		*save = NULL;
		return (temp);
	}
	else
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
}

void	*freeall(char *s1, char *s2)
{
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*buff;
	int			i;

	i = 1;
	if (fd == 1 || fd == 2 || fd > 1023 || fd < 0)
		return (NULL);
	if (!save[fd])
		save[fd] = (char *)gnl_calloc(1, 1);
	buff = (char *)gnl_calloc((BUFFER_SIZE + 1), 1);
	if (!save[fd] || !buff)
		return (freeall(save[fd], buff));
	while (!gnl_strchr(save[fd], '\n') && i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 1)
			break ;
		buff[i] = '\0';
		save[fd] = gnl_strjoin(save[fd], buff);
	}
	free(buff);
	return (gnlret(i, &save[fd]));
}
