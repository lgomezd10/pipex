#include "../includes/pipex.h"

void save_command(t_command *command)
{
	char *str;
	int fd;
	char **split;
	int i;

	command->argv = ft_split_set(command->command, " \t");
	split = ft_split("/usr/local/bin/:/usr/bin/:/bin/:/usr/sbin/:/sbin/", ':');
	if (!command->argv || !split)
		show_error("Malloc does not work", 0);
	fd = -1;
	str = 0;
	i = 0;
	while (split[i] != 0 && fd < 0)
	{
		free(str);
		str = ft_strjoin(split[i], command->argv[0]);
		fd = open(str, O_RDONLY);
		if (fd < 0)
			printf("error en %s\n", str);
		i++;
	}
	if (fd >= 0)
		command->command = str;
	else
	{
		free(str);
		show_error("Command not found", -1);
	}
	close(fd);
}

int load_command(t_command *command, char *str1, char *str2)
{
	int fd;

	printf("Se va a cargar el comando %s y %s\n", str1, str2);
	if (command->is_firts)
	{
		fd = open(str1, O_RDONLY);
		if (fd <  0)
			show_error("File 1  not found", 0);
		printf("Se puede abrir %s\n", str1);
		command->file_in = str1;
		command->command = str2;
		command->file_out = CACHE_FILE;
		save_command(command);
		close(fd);
	}
	else
	{
		command->command = str1;
		command->file_in = CACHE_FILE;
		save_command(command);
		if (str2)
		{
			fd = open(str2, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
			if (fd <  0)
				show_error("File 2 not found", 0);
			command->file_out = str2;
			close(fd);
		}
		else
		{
			command->file_out = CACHE_FILE;
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

void load_files(t_command *command)
{

	command->fd_in = open(command->file_in, O_RDONLY);
	command->fd_out = open(command->file_out, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	dup2(command->fd_in, STDIN_FILENO);
	dup2(command->fd_out, STDOUT_FILENO);
}

int exec_command(t_command *command)
{
	int pid;
	int status;

	printf("SE VA A EJECUTAR %s con entrada: %s y salida %s\n", command->command, command->file_in, command->file_out);
	pid = fork();
	if (pid == -1)
		show_error("error in fork", -1);
	else if (pid == 0)
	{
		load_files(command);
		execve(command->command, command->argv, 0);
		show_error("Error in exec", -1);
	} else
	{
		while(wait(&status) != pid);
		if (status == 0)
			printf("todo bien");
		else
			printf("error en el hijo");
		close(command->fd_in);
		close(command->fd_out);
	}
	return (0);
}