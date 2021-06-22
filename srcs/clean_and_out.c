/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 17:45:19 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/22 17:48:11 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void show_error(t_data *data, char *str, int error)
{
	ft_putstr_fd(NAME, 1);
	perror(str);
	clean_all(data);
	exit(error);
}

void show_error_command(t_data *data, char *resource)
{
	ft_putstr_fd(NAME, 1);
	ft_putstr_fd("command not found: ", 1);
	ft_putendl_fd(resource, 1);
	clean_all(data);
	exit(-1);
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