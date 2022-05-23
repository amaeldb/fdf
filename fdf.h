#ifndef FDF_H
# define FDF_H

// # include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include "get_next_line/get_next_line.h"

typedef struct s_vect{
	int	x;
	int	y;
}	t_vect;

typedef struct s_fdf{
	int		step;
	t_vect	start;
	t_vect	dim;
	int		**mat;
	double	ang;
}	t_fdf;

int		check_arg(char *argv, t_fdf *fdf);

void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(const char *s, char c);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
int		ft_printf(const char *str, ...);

#endif