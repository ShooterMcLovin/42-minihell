/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:20:03 by siroulea          #+#    #+#             */
/*   Updated: 2023/09/30 15:59:22 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*found_path(char *argv, char **env)
{
	char	**pathlist;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	pathlist = ft_split(env[i], ':');
	i = 0;
	while (pathlist[i])
	{
		temp = ft_strjoin(pathlist[i++], "/");
		path = ft_strjoin(temp, argv);
		if (access(path, F_OK) == 0)
		{
			return (path);
		}
	}
	return (0);
}

void	do_cmd(char *argv, char **env)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(argv, 32);
	if (!cmd)
	{
		free(cmd);
		perror("no command");
		exit(EXIT_FAILURE);
	}
	path = found_path(cmd[0], env);
	if (!path)
	{
		ft_free(path);
		perror("Command path not found");
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, env) == -1)
	{
		perror("execve error");
		exit(EXIT_FAILURE);
	}
	return ;
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

void	child_process(char *argv, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		do_cmd(argv, env);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	filein;
	int	fileout;
	

	if (argc >= 5)
	{
		i = 2;
		fileout = open_file(argv[argc - 1], 1);
		filein = open_file(argv[1], 2);
		dup2(filein, STDIN_FILENO);
		while (i < argc - 2)
			child_process(argv[i++], env);
		dup2(fileout, STDOUT_FILENO);
		close(filein);
		close(fileout);
		do_cmd(argv[argc - 2], env);
	}
}
