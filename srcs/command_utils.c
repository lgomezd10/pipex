#include "../includes/pipex.h"

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

void add_path(t_data *data, t_command *cmd)
{
	char *str;
	char *tmp;
	int fd;
	int i;

	cmd->argv = ft_split_set(cmd->pre_cmd, " \t");
	if (!cmd->argv)
		show_error(data, "Malloc does not work", 0);
	str = 0;
	i = 0;
	fd = open(cmd->argv[0], O_RDONLY);
	while (data->paths && data->paths[i] != 0 && fd < 0)
	{
		free(str);
		tmp = ft_strjoin(data->paths[i], "/");
		str = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		fd = open(str, O_RDONLY);
		i++;
	}
	if (fd >= 0)
		cmd->cmd = str;
	else
	{
		free(str);
		show_error_command(data, cmd->argv[0]);
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
            data->paths = ft_split(&str[5], ':');
            return (1);
        }
        i++;
    }
    show_error(data, "No path found in the environment", -1);
    return (0);
}