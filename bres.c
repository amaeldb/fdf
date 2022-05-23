#include "fdf.h"

#include <stdio.h>

void	place_pixel(int x, int y)
{
	//printf("(%d,%d) ", x, y);
}

void	bres_ur(t_fdf *fdf, t_vect start, t_vect end)
{
	t_vect	delt;
	int		pk;
	
	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.y - delt.x;
	while (start.x != end.x && start.y != end.y)
	{
		if (pk > 0)
		{
			place_pixel(start.x++, start.y++);
			pk += 2 * delt.y - 2 * delt.x;
		}
		else
		{
			place_pixel(start.x++, start.y);
			pk += 2 * delt.y;
		}	
	}
}

void	bres_uu(t_fdf *fdf, t_vect start, t_vect end)
{
	t_vect	delt;
	int		pk;
	
	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.x - delt.y;
	while (start.x != end.x && start.y != end.y)
	{
		if (pk > 0)
		{
			place_pixel(start.x++, start.y++);
			pk += 2 * delt.x - 2 * delt.y;
		}
		else
		{
			place_pixel(start.x, start.y++);
			pk += 2 * delt.x;
		}
	}
}

void	bres_dr(t_fdf *fdf, t_vect start, t_vect end)
{
	t_vect	delt;
	int		pk;
	
	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.y - delt.x;
	while (start.x != end.x && start.y != end.y)
	{
		if (pk < 0)
		{
			place_pixel(start.x++, start.y--);
			pk += 2 * delt.y - 2 * delt.x;
		}
		else
		{
			place_pixel(start.x++, start.y);
			pk += 2 * delt.y;
		}
	}
}

void	bres_dd(t_fdf *fdf, t_vect start, t_vect end)
{
	t_vect	delt;
	int		pk;
	
	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.x - delt.y;
	while (start.x != end.x && start.y != end.y)
	{
		if (pk < 0)
		{
			place_pixel(start.x++, start.y--);
			pk += 2 * delt.x - 2 * delt.y;
		}
		else
		{
			place_pixel(start.x, start.y--);
			pk += 2 * delt.x;
		}
	}
}