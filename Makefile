NAME = pipex

DIRLIBFT = libft

RM = rm -rf

LIBFT = ${DIRLIBFT}/libft.a

CFLAGS = -Wall -Wextra -Werror

FILES = main \
	handle_error \
	load_command \
	handle_path

SRCS = ${addsuffix .c, ${addprefix srcs/, ${FILES}}}

OBJS = ${SRCS:.c=.o}

${NAME} : ${LIBFT} ${OBJS}
	gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

all : ${NAME}

${LIBFT}:
	${MAKE} bonus -C ${DIRLIBFT}

clean:
	${RM} ${OBJS}
	${RM} ${OBJSMAIN}
	${RM} ${OBJSMAINBONUS}
	${MAKE} fclean -C ${DIRLIBFT}

fclean:	clean
	${RM} ${NAME}
	${RM} ${NAME_BONUS}