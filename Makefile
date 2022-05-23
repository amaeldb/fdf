SRCS	= window.c

OBJS	= ${SRCS:.c=.o}

FLAGS	= -Wall -Wextra -Werror

NAME	= fdf

.c.o:
	@ gcc ${FLAGS} -Imlx -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
	@ make -C libft --silent
	@ make -C mlx --silent
	@ gcc ${FLAGS} ${OBJS} libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME}
	@ echo "Successfully compiled: ${NAME}"

clean:	${OBJS}
	@ make clean -C libft --silent
	@ rm -rf ${OBJS}

fclean:	clean
	@ make fclean -C libft --silent
	@ rm -rf ${NAME}

re:	fclean
	@ make all
