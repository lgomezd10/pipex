#include "../includes/pipex.h"

static void run_firts_child(t_data *data, int pos)
{
	t_command	cmd;
	int			fd;

	cmd = data->cmds[pos];
	close(cmd.fd[READ_END]);
	dup2(cmd.fd[WRITE_END], STDOUT_FILENO);
	close(cmd.fd[WRITE_END]);
	fd = open(data->file_in, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	execve(cmd.cmd, cmd.argv, 0);
}

static void run_last_child(t_data *data, int pos)
{
	t_command	cmd;
	int			fd;

	cmd = data->cmds[pos];
	dup2(data->cmds[pos - 1].fd[READ_END], STDIN_FILENO);
	close(data->cmds[pos - 1].fd[READ_END]);
	fd = open(data->file_out, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve(cmd.cmd, cmd.argv, 0);
}

static void run_midle_child(t_data *data, int pos)
{
	t_command	cmd;

	cmd = data->cmds[pos];
	close(cmd.fd[READ_END]);
	dup2(data->cmds[pos - 1].fd[READ_END], STDIN_FILENO);
	close(data->cmds[pos - 1].fd[READ_END]);
	dup2(cmd.fd[WRITE_END], STDOUT_FILENO);
	close(cmd.fd[WRITE_END]);
	execve(cmd.cmd, cmd.argv, 0);
}


void run_commands2(t_data *data)
{
	pid_t	pid;
	int		i;
	int		status;

	i = 0;
	while (i < data->size_cmds)
	{
		printf("Iteración %d\n", i);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				printf("primer hijo\n");
				run_firts_child(data, i);
			}
			else if (i == data->size_cmds - 1)
			{
				printf("ultimo hijo\n");
				run_last_child(data, i);
			}
			else
			{
				printf("medio hijo\n");
				run_midle_child(data, i);
			}
		}
		else
		{
			if (i == 0)
				close(data->cmds[i].fd[WRITE_END]);
			if (i > 0 && i < data->size_cmds - 1)
			{
				close(data->cmds[i - 1].fd[READ_END]);
				close(data->cmds[i].fd[WRITE_END]);
			}
			i++;
		}
	}
	close(data->cmds[i - 2].fd[READ_END]);
	close(data->cmds[i - 1].fd[READ_END]);
	close(data->cmds[i - 1].fd[WRITE_END]);
	waitpid(pid, &status, 0);
}