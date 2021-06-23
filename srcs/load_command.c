/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 17:45:27 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/22 17:48:11 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
void load_temp_files(t_data *data)
{
	char *last;

	last = data->last_file_out;
	data->cmd.file_in = TMP_FILE_1;
	data->cmd.file_out = TMP_FILE_2;
	if (last && !ft_strncmp(last, TMP_FILE_2, sizeof(last)))
	{
		data->cmd.file_in = TMP_FILE_2;
		data->cmd.file_out = TMP_FILE_1;
	}
	data->last_file_out = data->cmd.file_out;
}
*/
void check_files(t_data *data)
{
	int fd;

	fd = open(data->file_in, O_RDONLY);
	if (fd < 0)
		show_error(data, data->file_in, -1);
	close(fd);
	fd = open(data->file_out, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	if (fd < 0)
		show_error(data, data->file_out, -1);
	close(fd);
}

/*
int load_command(t_data *data, t_command *cmd, char *str1, char *str2)
{
	if (cmd->is_firts)
	{
		data->cmd.file_in = str1;
		data->cmd.pre_cmd = str2;
		data->cmd.file_out = TMP_FILE_1;
	}
	else
	{
		data->cmd.pre_cmd = str1;
		load_temp_files(data);
		if (str2)
			data->cmd.file_out = str2;
	}
	check_files(data);
	add_path(data);
	return (0);
}*/

int run_command(t_data *data)
{
	int pid;
	int status;
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd;


	pipe(fd1);
	pipe(fd2);
	pid = fork();
	if (pid == -1)
		show_error(data, "error in fork", -1);
	else if (pid == 0)
	{
		close(fd1[WRITE_END]);
		close(fd2[READ_END]);
		dup2(fd1[READ_END], STDIN_FILENO);
		close(fd1[READ_END]);
		dup2(fd2[WRITE_END], STDOUT_FILENO);
		close(fd2[WRITE_END]);
	}
	else
	{
		close(fd1[READ_END]);
		close(fd2[WRITE_END]);
		fd = open(data->file_in, O_RDONLY);
		if (pid == -1)
			show_error(data, "error in fork", -1);
		else if (fd < 0)
			show_error(data, data->file_in, -1);
		dup2(fd, fd1[WRITE_END]);
		close(fd);
		pipe(fd3);
		pid = fork();
		if (pid == -1)
			show_error(data, "error in fork", -1);
		else if (pid == 0)
		{
			close(fd3[READ_END]);
			dup2(fd2[READ_END], STDIN_FILENO);
			close(fd2[READ_END]);
			dup2(fd3[WRITE_END], STDOUT_FILENO);
			close(fd3[WRITE_END]);
			//EJECUTAR COMANDO
		}
		else
		{
			close(fd3[WRITE_END]);
			fd = open(data->file_out, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
			dup2(fd3[READ_END], fd);
		}
	}

	wait(&status);
	wait(&status);
	wait(&status);
	close(fd);
	return (0);
}


/*
static void load_files(t_data *data)
{

	data->cmd.fd_in = open(data->cmd.file_in, O_RDONLY);
	data->cmd.fd_out = open(data->cmd.file_out, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	dup2(data->cmd.fd_in, STDIN_FILENO);
	dup2(data->cmd.fd_out, STDOUT_FILENO);
}



int exec_command(t_data *data)
{
	int pid;
	int status;

	pid = fork();
	if (pid == -1)
		show_error(data, "error in fork", -1);
	else if (pid == 0)
	{
		load_files(data);
		execve(data->cmd.cmd, data->cmd.argv, 0);
		show_error(data, "Error in exec", -1);
	} else
	{
		while(wait(&status) != pid);
		if (status == 0)
		{
			close(data->cmd.fd_in);
			close(data->cmd.fd_out);
		}
		else
			exit(-1);
	}
	return (0);
}*/