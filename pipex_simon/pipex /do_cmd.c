/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:06:19 by siroulea          #+#    #+#             */
/*   Updated: 2023/10/09 14:16:21 by siroulea         ###   ########.fr       */
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
		if (access(path, F_OK | X_OK) == 0)
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

	if (ft_strlen(argv) == 0 || argv[0] == ' ')
		error();
	cmd = ft_split(argv, 32);
	if (!cmd)
	{
		ft_free_double_array(cmd);
		error();
	}
	path = found_path(cmd[0], env);
	if (!path || ft_strlen(argv) == 0)
	{
		free(cmd);
		ft_free(path);
		error();
	}
	if (execve(path, cmd, env) == -1)
	{
		free(cmd);
		ft_free(path);
		error();
	}
	return ;
}
