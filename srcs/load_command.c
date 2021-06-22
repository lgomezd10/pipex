#include "../includes/pipex.h"



int load_command(t_data *data, char *str1, char *str2)
{
	int fd;

	printf("Se va a cargar el comando %s y %s\n", str1, str2);
	if (data->cmd.is_firts)
	{
		fd = open(str1, O_RDONLY);
		if (fd <  0)
			show_error("File 1  not found", 0);
		printf("Se puede abrir %s\n", str1);
		data->cmd.file_in = str1;
		data->cmd.cmd = str2;
		data->cmd.file_out = TMP_FILE_1;
		add_path(data);
		close(fd);
	}
	else
	{
		data->cmd.cmd = str1;
		data->cmd.file_in = TMP_FILE_1;
		data->cmd.file_out = TMP_FILE_2;
		printf("la salida al comparar %s y %s\n", data->last_file_out, TMP_FILE_2);
		if (data->last_file_out && !ft_strncmp(data->last_file_out, TMP_FILE_2, sizeof(data->last_file_out)))
		{
			data->cmd.file_in = TMP_FILE_2;
			data->cmd.file_out = TMP_FILE_1;
		}
		data->last_file_out = data->cmd.file_out;
		add_path(data);
		if (str2)
		{
			fd = open(str2, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
			if (fd <  0)
				show_error("File 2 not found", 0);
			data->cmd.file_out = str2;
			close(fd);
		}
		
	}
	return (0);
}

int print_split(char **argv)
{
	int i;

	i = 0;
	while (argv[i] != 0)
	{
		printf("argumento %d: %s\n", i, argv[i]);
		i++;
	}
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
		show_error("error in fork", -1);
	else if (pid == 0)
	{
		load_files(data);
		execve(data->cmd.cmd, data->cmd.argv, 0);
		show_error("Error in exec", -1);
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