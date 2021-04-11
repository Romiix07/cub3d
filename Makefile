SRCS		=	srcs/file_check/map_check_1.c			\
				srcs/file_check/map_check_2.c			\
				srcs/file_check/cub_parse.c				\
				srcs/file_check/parse_checks.c			\
				srcs/file_check/parse_utils.c			\
				srcs/file_check/memdel.c				\
				srcs/file_check/map_check_loop.c		\
				srcs/file_check/map_count.c				\
				srcs/file_check/last_check.c			\
				srcs/utils/ft_strcmp.c					\
				srcs/utils/ft_strncmp.c					\
				srcs/main.c								\
				srcs/utils/my_mlx_pixel_put.c			\
				srcs/utils/gnl/get_next_line.c			\
				srcs/utils/gnl/get_next_line_utils.c	\
				srcs/raycast/raycast_1.c				\
				srcs/raycast/raycast_2.c				\
				srcs/raycast/sprites.c					\
				srcs/raycast/sprites_color.c			\
				srcs/movements/move.c					\
				srcs/movements/rot.c					\
				srcs/screenshot/create_file.c			\
				srcs/init_game/init_game.c				\
				srcs/init_game/init_game_2.c			\
				srcs/events/events.c					\
				srcs/free/free.c

INCLUDES	=	-I./includes/	\
				-I./mlx/

OBJS		=$(SRCS:.c=.o)

NAME		=	cub3D

LIBS		=	-L/usr/lib -L./mlx -lmlx_Linux -lXext -lX11 -lm

CFLAGS      =   -Wall -Werror -Wextra

CC			=	gcc

RM			=	rm -f

.c.o:
				${CC} ${CFLAGS} -c -D BUFFER_SIZE=10 ${INCLUDES} ${LIBS} $< -o ${<:.c=.o}

${NAME}:		${OBJS}
				make -C mlx
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

all:			${NAME}

clean:
				${RM} ${OBJS}
				make clean -C mlx
				${RM} screenshot.bmp

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
