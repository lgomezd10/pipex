#include "../includes/pipex.h"

int main(int argc, char **argv, char **env)
{
	t_data data;
	int i;

	if (argc < 5)
		show_error(&data, "Wrong arguments", 0);
	ft_bzero(&data, sizeof(t_data));
	load_path(&data, env);
	i = 1;
	while (i < argc)
	{
		clean_command(&data);
		if (i == 1)
		{
			printf("se va a ejecutar la cabecera\n");
			data.cmd.is_firts = 1;
			load_command(&data, argv[i], argv[i + 1]);
			i += 2;
		}
		else if (i == argc - 2)
		{
			printf("para i: %d se va a ejecutar el final con\n", i);
			load_command(&data, argv[i], argv[i + 1]);
			i += 2;
			
		}
		else
		{
		   printf("se va a ejecutar un intermedio para i: %d\n", i);
			load_command(&data, argv[i++], 0);
		}
		exec_command(&data);
	}
	clean_all(&data);
}