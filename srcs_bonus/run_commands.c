/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:01:20 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/23 20:40:18 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	run_firts_child(t_data *data, int pos)
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
	show_error(data, "Error in exec");
}

static void	run_last_child(t_data *data, int pos)
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
	show_error(data, "Error in exec");
}

static void	run_midle_child(t_data *data, int pos)
{
	t_command	cmd;

	cmd = data->cmds[pos];
	close(cmd.fd[READ_END]);
	dup2(data->cmds[pos - 1].fd[READ_END], STDIN_FILENO);
	close(data->cmds[pos - 1].fd[READ_END]);
	dup2(cmd.fd[WRITE_END], STDOUT_FILENO);
	close(cmd.fd[WRITE_END]);
	execve(cmd.cmd, cmd.argv, 0);
	show_error(data, "Error in exec");
}

static void	close_fds(t_data *data, int pos)
{
	if (pos == 0)
		close(data->cmds[pos].fd[WRITE_END]);
	if (pos > 0 && pos < data->size_cmds - 1)
	{
		close(data->cmds[pos - 1].fd[READ_END]);
		close(data->cmds[pos].fd[WRITE_END]);
	}
}

void	run_commands(t_data *data)
{
	pid_t	pid;
	int		i;
	int		status;

	i = 0;
	while (i < data->size_cmds)
	{
		pid = fork();
		if (pid == -1)
			show_error(data, "Error in fork");
		if (pid == 0)
		{
			if (i == 0)
				run_firts_child(data, i);
			else if (i == data->size_cmds - 1)
				run_last_child(data, i);
			else
				run_midle_child(data, i);
		}
		else
			close_fds(data, i);
		i++;
	}
	close(data->cmds[i - 2].fd[READ_END]);
	waitpid(pid, &status, 0);
}
