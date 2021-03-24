SRCS		=	srcs/file_check/map_check_1.c			\
				srcs/file_check/map_check_2.c			\
				srcs/file_check/cub_parse.c				\
				srcs/file_check/parse_checks.c			\
				srcs/file_check/parse_utils.c			\
				srcs/utils/ft_strcmp.c					\
				srcs/utils/my_mlx_pixel_put.c			\
				srcs/utils/gnl/get_next_line.c			\
				srcs/utils/gnl/get_next_line_utils.c	\
				srcs/raycast/raycast_1.c				\
				srcs/raycast/raycast_2.c				\
				srcs/movements/move.c					\
				srcs/movements/rot.c					\
				srcs/init_game/init_game.c				\
				srcs/events/events.c					\
				srcs/free/free.c						\

INCLUDES	=	-I./includes/	\
				-I./mlx/

NAME		=	cub3D

LIBS		=	-L/usr/lib -L./mlx -lmlx_Linux -lXext -lX11 -lm -lz

CFLAGS      =   

CC			=	gcc

RM			=	rm -f

${NAME}:
				make -C mlx
				${CC} -o ${NAME} srcs/main.c ${SRCS} ${CFLAGS} -D BUFFER_SIZE=30 ${INCLUDES} ${LIBS}

all:			${NAME}

clean:
				find . -type f \( -name "*~" -o -name "#*#" -o -name "*.o" -o -name "*.gch" \) -delete

fclean:			clean
				make clean -C mlx
				${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
