SRCS	= fdf.c draw.c check.c bres.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

FLAGS	= -Wall -Wextra -Werror

MLX		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

NAME	= fdf

%.o: %.c
	@ gcc ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
	@ make -C libft --silent
	@ make -C mlx_linux --silent
	@ gcc ${FLAGS} -o ${NAME} ${OBJS} libft/libft.a ${MLX}
	@ echo "Successfully compiled: ${NAME}"

clean:	${OBJS}
	@ make clean -C libft --silent
	@ make clean -C mlx_linux --silent
	@ rm -rf ${OBJS}

fclean:	clean
	@ make fclean -C libft --silent
	@ rm -rf ${NAME}
	@ echo "Successfully removed: ${NAME}"

re:	fclean
	@ make all
