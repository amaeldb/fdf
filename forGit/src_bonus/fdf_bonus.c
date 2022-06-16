/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:55 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/16 11:06:03 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	else if (key == 65364 && fdf->step > 1)
		fdf->step -= fdf->step / 10 + 1;
	else if (key == 100)
		fdf->start.x -= 50;
	else if (key == 97)
		fdf->start.x += 50;
	else if (key == 119)
		fdf->start.y += 50;
	else if (key == 115)
		fdf->start.y -= 50;
	else if (key == 99)
		set_col(fdf, (int [7]){65535, 255, 16711935, 16711680, 16776960,
			65280, 0}, (int [7]){65536, 65792, 256, 257, 1, 65537, 65793});
	draw(fdf);
	return (0);
}

void	set_step(t_fdf *fdf)
{
	int	xx;
	int	xy;
	int	y;

	fdf->step = 25;
	while (--fdf->step)
	{
		xx = fdf->step * fdf->dim.x * 2;
		xy = fdf->step * fdf->dim.y * 2;
		y = fdf->step * (fdf->dim.x + fdf->dim.y - 2);
		fdf->start.x = 960 - (xx - xy) / 2;
		fdf->start.y = 540 - (y / 2);
		if (fdf->step == 1 || (fdf->start.x + xx < 1920
				&& fdf->start.y + y < 1080))
			break ;
	}
}

void	set_fdf(t_fdf *fdf, char *str)
{
	set_step(fdf);
	fdf->col_step = 0;
	if (fdf->max_z != fdf->min_z)
		fdf->col_step = 255 / (fdf->max_z - fdf->min_z);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		frexit(fdf);
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, str);
	if (!fdf->win)
		frexit(fdf);
	fdf->color.x = 65535;
	fdf->color.y = 65536;
	fdf->color.z = 0;
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
