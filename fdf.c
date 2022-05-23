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
		fdf->start = (t_vect){150, 150 + (fdf->step * (fdf->dim.x - fdf->dim.y)) / 2};
	}
	else
	{
		fdf->step = 700 / (fdf->dim.y - 1);
		fdf->start = (t_vect){150 + (fdf->step * (fdf->dim.y - fdf->dim.x)) / 2, 150};
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