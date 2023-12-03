/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:09:12 by siroulea          #+#    #+#             */
/*   Updated: 2023/10/09 14:16:35 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_fd(void)
{
	t_data	*data;
	int		j;

	data = get_data();
	j = 0;
	while (j < data->nb_child - 1)
	{
		data->fd[j] = ft_calloc(2, sizeof(int));
		if (pipe(data->fd[j]) == -1)
			error();
		j++;
	}
}

void	open_filein(int argc, char **argv)
{
	t_data	*data;

	data = get_data();
	data->fileout = open_file(argv[argc - 1], 1);
	data->filein = open_file(argv[1], 2);
	dup2(data->filein, STDIN_FILENO);
}

void	loop_fork(int argc, char **argv, char **env)
{
	pid_t	pid;
	t_data	*data;
	int		i;
	int		j;

	(void)argv;
	data = get_data();
	j = 0;
	i = 2;
	while (j < data->nb_child)
	{
		pid = fork();
		if (pid == -1)
			error();
		else if (pid == 0)
			child(i, j, argc, env);
		else
			data->child_pid[j] = pid;
		i++;
		j++;
	}
}

void	close_fd(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	close(data->filein);
	close(data->fileout);
	while (i < data->nb_child - 1)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

void	free_all(void)
{
	t_data	*data;

	data = get_data();
	close_fd();
	ft_free_fd();
	free(data->fd);
	free(data->child_pid);
	free(data);
}
