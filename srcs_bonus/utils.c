/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:30:06 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/23 20:40:39 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	find_path(t_data *data, t_command *cmd, char **str)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(cmd->argv[0], O_RDONLY);
	i = 0;
	while (data->paths && data->paths[i] != 0 && fd < 0)
	{
		free(*str);
		tmp = ft_strjoin(data->paths[i], "/");
		*str = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		fd = open(*str, O_RDONLY);
		i++;
	}
	close(fd);
	return (fd);
}

void	add_path(t_data *data, t_command *cmd)
{
	char	*str;
	int		fd;

	cmd->argv = ft_split_set(cmd->pre_cmd, " \t");
	if (!cmd->argv)
		show_error(data, "Malloc does not work");
	str = 0;
	fd = find_path(data, cmd, &str);
	if (fd >= 0)
		cmd->cmd = str;
	else
	{
		free(str);
		show_error_command(data, cmd->argv[0]);
	}
}

int	load_path(t_data *data, char **env)
{
	int		i;
	char	*str;

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
	show_error(data, "No path found in the environment");
	return (0);
}

void	check_files(t_data *data)
{
	int	fd;

	if (!data->limiter)
	{
		fd = open(data->file_in, O_RDONLY);
		if (fd < 0)
			show_error(data, data->file_in);
		close(fd);
	}
	fd = open(data->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		show_error(data, data->file_out);
	close(fd);
}

void	save_command(t_data *data, t_command *cmd, char *argv)
{
	cmd->pre_cmd = argv;
	add_path(data, cmd);
	pipe(cmd->fd);
}
