#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# define CACHE_FILE "ficherocache"

typedef struct s_command
{
    char *file_in;
    char *file_out;
    char *command;
    char **argv;
    char    *evd;
    int     is_firts;
    int     fd_in;
    int     fd_out;
} t_command;

void show_error(char *str, int error);
int load_command(t_command *command, char *str1, char *str2);
int exec_command(t_command *command);
#endif