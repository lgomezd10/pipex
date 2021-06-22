#include "../includes/pipex.h"

int main(int argc, char **argv, char **env)
{
	t_data data;
	int i;

	ft_bzero(&data, sizeof(t_data));
	if (argc < 5)
		show_error(&data, "At least three arguments are required", 0);
	load_path(&data, env);
	i = 1;
	while (i < argc)
	{
		clean_command(&data);
		if (i == 1)
		{
			data.cmd.is_firts = 1;
			load_command(&data, argv[i], argv[i + 1]);
			i += 2;
		}
		else if (i == argc - 2)
		{
			load_command(&data, argv[i], argv[i + 1]);
			i += 2;
		}
		else
			load_command(&data, argv[i++], 0);
		exec_command(&data);
	}
	clean_all(&data);
}