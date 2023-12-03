/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:20:03 by siroulea          #+#    #+#             */
/*   Updated: 2023/10/09 14:17:34 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		data = ft_calloc(1, sizeof(t_data));
		return (data);
	}
	return (data);
}

void	ft_free_fd(void)
{
	int		i;
	t_data	*data;

	data = get_data();
	i = 0;
	while (i < data->nb_child - 1)
	{
		free(data->fd[i]);
		i++;
	}
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

void	child(int i, int j, int argc, char **env)
{
	t_data	*data;

	data = get_data();
	if (i == argc - 2)
	{
		dup2(data->fd[j - 1][0], STDIN_FILENO);
		dup2(data->fileout, STDOUT_FILENO);
		close_fd();
		do_cmd(data->ar[argc - 2], env);
	}
	else if (i == 2)
	{
		dup2(data->fd[j][1], STDOUT_FILENO);
		close_fd();
		do_cmd(data->ar[i], env);
	}
	else
	{
		dup2(data->fd[j - 1][0], STDIN_FILENO);
		dup2(data->fd[j][1], STDOUT_FILENO);
		close_fd();
		do_cmd(data->ar[i], env);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		j;

	j = 0;
	if (argc >= 5)
	{
		data = get_data();
		data->ar = argv;
		data->nb_child = argc - 3;
		data->fd = ft_calloc(data->nb_child - 1, sizeof(int *));
		data->child_pid = malloc(data->nb_child * sizeof(pid_t));
		pipe_fd();
		open_filein(argc, argv);
		loop_fork(argc, argv, env);
		close_fd();
		while (j < data->nb_child)
			waitpid(data->child_pid[j++], NULL, 0);
		free_all();
	}
	else
		error();
	return (0);
}
