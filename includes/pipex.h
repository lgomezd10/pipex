#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# define TMP_FILE_1 "temp1"
# define TMP_FILE_2 "temp2"

typedef struct s_command
{
    char *file_in;
    char *file_out;
    char *cmd;
    char **argv;
    char    *evd;
    int     is_firts;
    int     fd_in;
    int     fd_out;
} t_command;

typedef struct s_data
{
    t_command   cmd;
    int         argc;
    char        **paths;
    char        *last_file_out;
} t_data;

void show_error(char *str, int error);
int load_command(t_data *data, char *str1, char *str2);
int exec_command(t_data *data);
void add_path(t_data *data);
int load_path(t_data *data, char **env);
#endif