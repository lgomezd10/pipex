NAME = pipex

DIRLIBFT = libft

RM = rm -rf

LIBFT = ${DIRLIBFT}/libft.a

CFLAGS = -Wall -Wextra -Werror

FILES = main \
	clean_and_out \
	utils \
	run_commands

SRCS = ${addsuffix .c, ${addprefix srcs/, ${FILES}}}

FILESBONUS = ${FILES} bonus utils_run

SRCSBONUS = ${addsuffix .c, ${addprefix srcs_bonus/, ${FILESBONUS}}}

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCSBONUS:.c=.o}

${NAME} : ${LIBFT} ${OBJS}
	gcc -g ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

bonus : ${LIBFT} ${OBJSBONUS}
	gcc -g ${CFLAGS} -o ${NAME} ${OBJSBONUS} ${LIBFT}

all : ${NAME}

${LIBFT}:
	${MAKE} bonus -C ${DIRLIBFT}

clean:
	${RM} ${OBJS}
	${RM} ${OBJSBONUS}
	${MAKE} fclean -C ${DIRLIBFT}

fclean:	clean
	${RM} ${NAME}

re:		fclean all

.PHONY:	all bonus clean fclean re