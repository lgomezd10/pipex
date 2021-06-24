#include "../includes/bonus.h"

void	close_fds(t_data *data, int pos)
{
	if (pos == 0)
		close(data->cmds[pos].fd[WRITE_END]);
	if (pos > 0 && pos < data->size_cmds - 1)
	{
		close(data->cmds[pos - 1].fd[READ_END]);
		close(data->cmds[pos].fd[WRITE_END]);
	}
}