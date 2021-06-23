/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:38:16 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/23 20:42:01 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# define TMP_FILE_1 "temp1"
# define TMP_FILE_2 "temp2"
# define NAME "pipex: "
# define READ_END 0
# define WRITE_END 1

typedef struct s_command
{
	char	*cmd;
	char	*pre_cmd;
	char	**argv;
	int		is_firts;
	int		fd_in;
	int		fd_out;
	int		fd[2];
}	t_command;

typedef struct s_data
{
	t_command	*cmds;
	int			size_cmds;
	int			argc;
	char		**paths;
	char		*last_file_out;
	char		*file_in;
	char		*file_out;
}	t_data;

void	show_error(t_data *data, char *str);
void	show_error_command(t_data *data, char *resource);
void	check_files(t_data *data);
void	save_command(t_data *data, t_command *cmd, char *argv);
void	clean_all(t_data *data);
void	add_path(t_data *data, t_command *cmd);
int		load_path(t_data *data, char **env);
void	run_commands(t_data *data);
#endif