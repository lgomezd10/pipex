#include "../includes/pipex.h"

t_command  *add_new_command(t_data *data)
{
	t_command *cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	ft_lstadd_back(data->cmds, ft_lstnew(cmd));
	return (cmd);
}

int main(int argc, char **argv, char **env)
{
	t_data data;
	int i;
	t_command *cmd;

	ft_bzero(&data, sizeof(t_data));
	if (argc < 5)
		show_error(&data, "At least three arguments are required", 0);
	data.cmds = ft_calloc(sizeof(t_command), argc - 2);
	load_path(&data, env);
	i = 0;
	data.file_in = argv[i++];
	data.file_out = argv[argc - 1];
	data.size_cmds = argc - 3;
	while (i < data.size_cmds)
	{
		data.cmds[i].pre_cmd = argv[i + 2];
		i++;
	}
	clean_all(&data);
}