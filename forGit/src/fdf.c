/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:55 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/14 13:16:19 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	frexit(t_fdf *fdf)
{
	int	i;

	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	i = -1;
	while (++i < fdf->dim.y)
		free(fdf->mat[i]);
	free(fdf->mat);
	free(fdf);
	exit(0);
}

int	modif(int key, t_fdf *fdf)
{
	if (key == 0xff1b)
		frexit(fdf);
	else if (key == 65362 && (fdf->step / 10 + 1) < 2147483647)
		fdf->step += fdf->step / 10 + 1;
	else if (key == 65364 && fdf->step > 0)
		fdf->step -= fdf->step / 10 + 1;
	else if (key == 0xff25)
		fdf->ang -= 15 * M_PI / 180;
	else if (key == 0xff27)
		fdf->ang += 15 * M_PI / 180;
	else if (key == 100)
		fdf->start.x += 50;
	else if (key == 97)
		fdf->start.x -= 50;
	else if (key == 119)
		fdf->start.y -= 50;
	else if (key == 115)
		fdf->start.y += 50;
	if (fdf->ang > 6.1 || fdf->ang < -6.1)
		fdf->ang = 0;
	draw(fdf);
	return (0);
}

void	set_fdf(t_fdf *fdf, char *str)
{
	if (fdf->dim.x > fdf->dim.y)
	{
		fdf->step = 300 / (fdf->dim.x - 1);
		fdf->start = (t_vect){250, 450 + (fdf->step * (fdf->dim.x - fdf->dim.y))
			/ 2};
	}
	else
	{
		fdf->step = 300 / (fdf->dim.y - 1);
		fdf->start = (t_vect){450 + (fdf->step * (fdf->dim.y - fdf->dim.x))
			/ 2, 250};
	}
	fdf->ang = 15 * M_PI / 180;
	fdf->col_step = 0;
	if (fdf->max_z != fdf->min_z)
		fdf->col_step = 255 / (fdf->max_z - fdf->min_z);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		frexit(fdf);
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, str);
	if (!fdf->win)
		frexit(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		return (0);
	if (argc != 2 || check_arg(argv[1], fdf))
	{
		free(fdf);
		return (0);
	}	
	set_fdf(fdf, argv[1]);
	draw(fdf);
	mlx_key_hook(fdf->win, modif, fdf);
	mlx_hook(fdf->win, 17, 1, frexit, fdf);
	mlx_loop(fdf->mlx);
}
