SRCS	= test.c

OBJS	= ${SRCS:.c=.o}

#FLAGS	= -Wall -Wextra -Werror
FLAGS	= 

NAME	= fdf

%.o: %.c
	@ gcc ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
	@ make -C libft --silent
	@ make -C mlx_linux --silent
	@ gcc ${FLAGS} ${OBJS} libft/libft.a -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME}
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
