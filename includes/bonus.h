#ifndef BONUS_H
# define BONUS_H
# include "pipex.h"
#endif

int has_limiter(t_data *data, int argc, char **argv);
void run_limitator(t_data *data);
void	close_fds(t_data *data, int pos);