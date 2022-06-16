/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:49 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/16 15:19:36 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_mat(char *str, t_fdf *fdf, int y, int x)
{
	int	i;

	i = -1;
	if (!fdf->mat[y])
		return (1);
	while (str[++i])
		if (((i == 0 && str[i] != '-') && !ft_isdigit(str[i]))
			&& str[i] != '\n')
			return (1);
	fdf->mat[y][x] = ft_atoi((const char *)str);
	if (fdf->mat[y][x] < fdf->min_z)
		fdf->min_z = fdf->mat[y][x];
	else if (fdf->mat[y][x] > fdf->max_z)
		fdf->max_z = fdf->mat[y][x];
	return (0);
}

int	freee(char **temp, t_fdf *fdf, int y, char *str)
{
	int	i;

	i = -1;
	if (str)
		free(str);
	if (temp)
	{
		while (temp[++i])
			free(temp[i]);
		free(temp);
	}
	if (y != -1)
	{
		i = -1;
		while (++i <= y)
			free(fdf->mat[i]);
		free(fdf->mat);
	}
	return (1);
}

char	**set_check(t_fdf *fdf, int fd)
{
	char	*delete;
	char	**temp;

	delete = get_next_line(fd);
	temp = ft_split(delete, ' ');
	free(delete);
	if (!temp)
		return (NULL);
	fdf->min_z = ft_atoi((const char *)temp[0]);
	fdf->dim.x = count_lines(0, temp);
	return (temp);
}

int	check_too(int fd, t_fdf *fdf)
{
	int		i;
	char	**temp;
	char	*delete;
	int		y;

	temp = set_check(fdf, fd);
	delete = NULL;
	if (!temp)
		return (1);
	y = -1;
	while (temp)
	{
		i = -1;
		fdf->mat[++y] = calloc(fdf->dim.x, sizeof(int));
		while (temp[++i] && temp[i][0] != '\n')
			if (i == fdf->dim.x || set_mat(temp[i], fdf, y, i))
				return (freee(temp, fdf, y, delete));
		if (i != fdf->dim.x)
			return (freee(temp, fdf, y, delete));
		freee(temp, fdf, -1, delete);
		delete = get_next_line(fd);
		temp = ft_split(delete, ' ');
	}
	return (0);
}

int	check_arg(char *argv, t_fdf *fdf)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (1);
	fdf->dim.y = count_lines(fd, NULL);
	close(fd);
	if (!fdf->dim.y)
		return (freee(NULL, fdf, -1, NULL));
	fdf->dim.x = 0;
	fdf->mat = ft_calloc(1, sizeof(int *) * fdf->dim.y);
	fd = open(argv, O_RDONLY);
	if (check_too(fd, fdf))
	{
		(void)count_lines(fd, NULL);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
