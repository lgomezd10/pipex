/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgomez-d <lgomez-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:33:46 by lgomez-d          #+#    #+#             */
/*   Updated: 2021/06/24 15:33:48 by lgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	close_fds(t_data *data, int pos)
{
	if (pos == 0)
		close(data->cmds[pos].fd[WRITE_END]);
	if (pos > 0 && pos < data->size_cmds - 1)
	{
		close(data->cmds[pos - 1].fd[READ_END]);
		close(data->cmds[pos].fd[WRITE_END]);
	}
}
