/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 19:51:39 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/23 20:51:16 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"



int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;

	ft_bzero(&data, sizeof(t_data));
	if (argc < 5)
		show_error(&data, "At least four arguments are required");
	data.cmds = ft_calloc(sizeof(t_command), argc - 2);
	load_path(&data, env);
	if (!has_limiter(&data, argc, argv))
	{
		data.size_cmds = argc - 3;
		data.file_in = argv[1];
		data.file_out = argv[argc - 1];
		check_files(&data);
		i = 0;
		while (i < data.size_cmds)
		{
			save_command(&data, &data.cmds[i], argv[i + 2]);
			i++;
		}
		run_commands(&data);
	}
	clean_all(&data);
}
