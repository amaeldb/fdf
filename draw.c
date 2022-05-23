#include "fdf.h"

void	find_dir(t_fdf *fdf, t_vect start, t_vect end)
{
	int	delt_x;
	int	delt_y;

	delt_x = end.x - start.x;
	delt_y = end.y - start.y;
	if (delt_x >= delt_y && delt_x > -1 && delt_y > -1)
		bres_ur(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y < 1)
		bres_ur(fdf, end, start);
	else if (delt_x < delt_y && delt_x > -1 && delt_y > -1)
		bres_uu(fdf, start, end);
	else if (delt_x > delt_y && delt_x < 1 && delt_y < 1)
		bres_uu(fdf, end, start);
	else if (delt_x >= delt_y && delt_x > -1 && delt_y < 1)
		bres_dr(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y > -1)
		bres_dr(fdf, end, start);
	else if (delt_x < delt_y && delt_x > -1 && delt_y < 1)
		bres_dd(fdf, start, end);
	else if (delt_x > delt_y && delt_x < 1 && delt_y > -1)
		bres_dd(fdf, end, start);
}

void	draw_line(t_fdf *fdf, t_vect start, t_vect end)
{
	start.x = (int)((cos(fdf->ang) * (fdf->start.x + fdf->step * start.x - 500)) -
		(sin(fdf->ang) * (fdf->start.y + fdf->step * start.y - 500)) + 500);
	start.y = (int)((cos(fdf->ang) * (fdf->start.y + fdf->step * start.y - 500)) +
		(sin(fdf->ang) * (fdf->start.x + fdf->step * start.x - 500)) + 500)
			+ fdf->step / 5 * fdf->mat[start.y][start.x];
	end.x = (int)((cos(fdf->ang) * (fdf->start.x + fdf->step * start.x - 500)) -
		(sin(fdf->ang) * (fdf->start.y + fdf->step * start.y - 500)) + 500);
	end.y = (int)((cos(fdf->ang) * (fdf->start.y + fdf->step * start.y - 500)) +
		(sin(fdf->ang) * (fdf->start.x + fdf->step * start.x - 500)) + 500)
		+ fdf->step / 5 * fdf->mat[end.y][end.x];
	find_dir(fdf, start, end);
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->dim.y)
	{
		x = -1;
		while (++x < fdf->dim.x)
		{
			if (x > 0)
				draw_line(fdf, (t_vect){x - 1, y}, (t_vect){x, y});
			if (y > 0)
				draw_line(fdf, (t_vect){x, y - 1}, (t_vect){x, y});
		}
	}
}