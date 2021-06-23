#include "../includes/pipex.h"


void save_command(t_data *data, t_command *cmd, char *argv)
{
	cmd->pre_cmd = argv;
	add_path(data, cmd);
	pipe(cmd->fd);
}

int main(int argc, char **argv, char **env)
{
	t_data data;
	int i;

	ft_bzero(&data, sizeof(t_data));
	if (argc < 5)
		show_error(&data, "At least three arguments are required", 0);
	data.cmds = ft_calloc(sizeof(t_command), argc - 2);
	load_path(&data, env);
	
	
	data.file_out = argv[argc - 1];
	data.size_cmds = argc - 3;
	i = 0;
	data.file_in = argv[i + 1];
	while (i < data.size_cmds)
	{
		printf("total: %d el argumento a guardar es %s\n", data.size_cmds, argv[i + 2]);
		save_command(&data, &data.cmds[i], argv[i + 2]);
		i++;
	}
	i = 0;
	while (i < data.size_cmds)
	{
		printf("command: %s \n", data.cmds[i].cmd);
		print_split(data.cmds[i].argv);
		i++;
	}
	run_commands2(&data);
	
	clean_all(&data);
	ft_bzero(&data, sizeof(t_data));
	system("leaks pipex");
}