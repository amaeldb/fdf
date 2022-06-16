SRCS	= src/fdf.c src/draw.c src/check.c src/bres.c src/count.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRCSB	= src_bonus/fdf_bonus.c src_bonus/draw_bonus.c src_bonus/check_bonus.c src_bonus/bres_bonus.c src_bonus/count_bonus.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

OBJSB	= ${SRCSB:.c=.o}

DEPS	= ${OBJS:.o=.d}

DEPSB	= ${OBJSB:.o=.d}

FLAGS	= -MMD -Wall -Wextra -Werror

MLX		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

NAME	= fdf

NAMEB	= fdf_bonus

%.o: %.c
	@ gcc ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

all:	${NAME}

bonus:	${NAMEB}

${NAME}:	${OBJS}
	@ make -C libft --silent
	@ make -C mlx_linux --silent
	@ gcc ${FLAGS} -o ${NAME} ${OBJS} libft/libft.a ${MLX}
	@ echo "Successfully compiled: ${NAME}"

${NAMEB}:	${OBJSB}
	@ make -C libft --silent
	@ make -C mlx_linux --silent
	@ gcc ${FLAGS} -o ${NAMEB} ${OBJSB} libft/libft.a ${MLX}
	@ echo "Successfully compiled bonus: ${NAMEB}"

clean:	${OBJS} ${OBJSB}
	@ make clean -C libft --silent
	@ make clean -C mlx_linux --silent
	@ rm -rf ${OBJS} ${OBJSB} ${DEPS} ${DEPSB}

fclean:	clean
	@ make fclean -C libft --silent
	@ rm -rf ${NAME} ${NAMEB}
	@ echo "Successfully removed: ${NAME}"

re:	fclean
	@ make all

-include ${DEPS}
-include ${DEPSB}