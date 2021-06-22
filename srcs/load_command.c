#include "../includes/pipex.h"

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

void check_files(t_data *data)
{
	int fd;

	fd = open(data->cmd.file_in, O_RDONLY);
	if (fd < 0)
		show_error(data, data->cmd.file_in, -1);
	printf("el FD es %d\n", fd);
	close(fd);
	fd = open(data->cmd.file_out, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	if (fd < 0)
		show_error(data, data->cmd.file_out, -1);
	close(fd);
}

int load_command(t_data *data, char *str1, char *str2)
{
	printf("Se va a cargar el comando %s y %s\n", str1, str2);
	if (data->cmd.is_firts)
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
		printf("COMANDO %s\n", data->cmd.cmd);
	}
	check_files(data);
	add_path(data);
	return (0);
}

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

	printf("SE VA A EJECUTAR %s con entrada: %s y salida %s\n", data->cmd.cmd, data->cmd.file_in, data->cmd.file_out);
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
			printf("todo bien");
		else
			printf("error en el hijo");
		close(data->cmd.fd_in);
		close(data->cmd.fd_out);
	}
	return (0);
}