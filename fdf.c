/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:55 by ade-beta          #+#    #+#             */
/*   Updated: 2022/05/25 17:03:38 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (argc != 2 || check_arg(argv[1], fdf))
	{
		free(fdf);
		return (0);
	}	
	if (fdf->dim.x > fdf->dim.y)
	{
		fdf->step = 700 / (fdf->dim.x - 1);
		fdf->start = (t_vect){150, 150 + (fdf->step * (fdf->dim.x - fdf->dim.y))
			/ 2};
	}
	else
	{
		fdf->step = 700 / (fdf->dim.y - 1);
		fdf->start = (t_vect){150 + (fdf->step * (fdf->dim.y - fdf->dim.x))
			/ 2, 150};
	}
	fdf->ang = 15 * M_PI / 180;



	int x = -1, y = -1;
	while (++y < fdf->dim.y)
	{
		x = -1;
		while (++x < fdf->dim.x)
			printf("(%d, %d) ", (int)((cos(fdf->ang) * (fdf->start.x + fdf->step * x - 500)) -
			(sin(fdf->ang) * (fdf->start.y + fdf->step * y - 500)) + 500), 
			(int)((cos(fdf->ang) * (fdf->start.y + fdf->step * y - 500)) +
			(sin(fdf->ang) * (fdf->start.x + fdf->step * x - 500)) + 500)
			+ fdf->step / 33 * fdf->mat[y][x]);
		printf("\n");
	}

	int i = -1, j = -1;

	while (++i < fdf->dim.y)
	{
		j = -1;
		while (++j < fdf->dim.x)
			ft_printf("%d ", fdf->mat[i][j]);
		ft_printf("\n");
	}

	i = -1;
	while (++i < fdf->dim.y)
		free(fdf->mat[i]);
	free(fdf->mat);
	free(fdf);
}