/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:07:25 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/24 20:38:00 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

static void	run_child(t_data *data)
{
	t_list	*list;
	int		readed;
	char	*str;

	str = 0;
	readed = 1;
	list = 0;
	close(data->cmds[0].fd[READ_END]);
	while (readed && (!str || ft_strncmp(str, data->limiter, sizeof(str))))
	{
		ft_putstr_fd("> ", 1);
		readed = get_next_line(0, &str);
		ft_lstadd_back(&list, ft_lstnew(str));
	}
	close(data->cmds[0].fd[READ_END]);
	dup2(data->cmds[0].fd[WRITE_END], STDOUT_FILENO);
	close(data->cmds[0].fd[WRITE_END]);
	while (list->next)
	{
		ft_putendl_fd((char *)list->content, 1);
		list = list->next;
	}
	ft_lstclear(&list, free);
	exit (0);
}

static void	run_limitator(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		show_error(data, "Error in fork");
	else if (pid == 0)
	{
		run_child(data);
	}
	else
	{
		close(data->cmds[0].fd[WRITE_END]);
		run_commands(data);
		wait(&status);
	}
}

int	has_limiter(t_data *data, int argc, char **argv)
{
	int	i;

	if (!ft_strncmp(argv[1], "here_doc", sizeof(argv[1])))
	{
		if (argc < 6)
			show_error(data, \
			"With parameter \"hear_doc\", at least five arguments are required");
		data->limiter = argv[2];
		data->size_cmds = argc - 3;
		data->file_out = argv[argc - 1];
		check_files(data);
		save_command(data, &data->cmds[0], argv[3]);
		i = 1;
		while (i < data->size_cmds)
		{
			save_command(data, &data->cmds[i], argv[i + 2]);
			i++;
		}
		run_limitator(data);
		return (1);
	}
	return (0);
}
