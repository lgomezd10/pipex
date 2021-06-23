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

OBJS = ${SRCS:.c=.o}

${NAME} : ${LIBFT} ${OBJS}
	gcc -g ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}

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