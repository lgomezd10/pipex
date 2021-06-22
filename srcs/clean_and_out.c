#include "../includes/pipex.h"

void show_error(t_data *data, char *str, int error)
{
	clean_all(data);
	perror(str);
	exit(error);
}

void free_split(char **split)
{
	int i;

	if (split)
	{
		i = 0;
		while (split[i] != 0)
		{
			free(split[i]);
			split[i] = 0;
			i++;
		}
		free(split);
	}
}

void clean_command(t_data *data)
{
	free_split(data->cmd.argv);
	free(data->cmd.cmd);
	ft_bzero(&data->cmd, sizeof(t_command));
}

void clean_all(t_data *data)
{
	clean_command(data);
	free_split(data->paths);
}