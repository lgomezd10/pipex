#include "../includes/pipex.h"

void show_error(char *str, int error)
{
    perror(str);
    exit(error);
}