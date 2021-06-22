#include "../includes/pipex.h"

void add_path(t_data *data)
{
	char *str;
	char *tmp;
	int fd;
	int i;

	data->cmd.argv = ft_split_set(data->cmd.cmd, " \t");
	if (!data->cmd.argv)
		show_error("Malloc does not work", 0);
	str = 0;
	i = 0;
	fd = open(data->cmd.argv[0], O_RDONLY);
	while (data->paths[i] != 0 && fd < 0)
	{
		free(str);
		tmp = ft_strjoin(data->paths[i], "/");
		str = ft_strjoin(tmp, data->cmd.argv[0]);
		free(tmp);
		fd = open(str, O_RDONLY);
		if (fd < 0)
			printf("No funciona la ruta %s\n", str);
		i++;
	}
	if (fd >= 0)
		data->cmd.cmd = str;
	else
	{
		free(str);
		show_error("Command not found", -1);
	}
	close(fd);
}

int load_path(t_data *data, char **env)
{
    int i;
    char *str;

    i = 0;
    while (env[i] != 0)
    {
        str = ft_strnstr(env[i], "PATH=", 5);
        if (str)
        {
            data->paths = ft_split(str, ':');
            return (1);
        }
        i++;
    }
    show_error("No path found in the environment", -1);
    return (0);
}