SRCS		=	

INCLUDES	=	../include

OBJS		=	${SRCS:.c=.o}

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

NAME		=	libftprintf.a

CFLAGS		=	-Wall -Wextra -Werror

CC			=	clang

RM			=	rm -f

.c.o:
				${CC} ${CFLAGS} -I${INCLUDES} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
				ar rc ${NAME} ${OBJS}

all:			${NAME}

bonus:			${NAME}

clean:
				${RM} ${OBJS} ${OBJS_BONUS}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
