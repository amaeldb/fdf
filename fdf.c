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

int	frexit(t_fdf *fdf)
{
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	exit(0);
}

void	modif(int key, t_fdf *fdf)
{
	if (key == 0xff1b)
		frexit(fdf);
	else if (key == 0xff26)
		fdf->step += fdf->step / 10;
	else if (key == 0xff28)
		fdf->step -= fdf->step / 10;
	else if (key == 0xff25)
		fdf->ang -= 15 * M_PI / 180;
	else if (key == 0xff27)
		fdf->ang += 15 * M_PI / 180;
	else if (key == 0xff41)
		fdf->start.x -= 50;
	else if (key == 0xff44)
		fdf->start.x += 50;
	else if (key == 0xff57)
		fdf->start.y += 50;
	else if (key == 0xff53)
		fdf->start.x -= 50;
	if (fdf->ang > 6.1 || fdf->ang < -6.1)
		fdf->ang = 0;
	draw(fdf);
}

void	set_fdf(t_fdf *fdf, char *str)
{
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
	fdf->col_step = 255 / (fdf->max_z - fdf->min_z);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1000, 1000, str);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (argc != 2 || check_arg(argv[1], fdf))
	{
		free(fdf);
		return (0);
	}	
	set_fdf(fdf, argv[1]);
	draw(fdf);

	// TESTS

	int i = -1, j = -1;

	while (++i < fdf->dim.y)
	{
		j = -1;
		while (++j < fdf->dim.x)
			ft_printf("%d ", fdf->mat[i][j]);
		ft_printf("\n");
	}

	ft_printf("min_z = %d, max_z = %d, col_step = %d\n", fdf->min_z, fdf->max_z, fdf->col_step);
	i = -1;
	while (++i < fdf->dim.y)
		free(fdf->mat[i]);
	free(fdf->mat);
	free(fdf);
}