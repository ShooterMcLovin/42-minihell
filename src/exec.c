/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:35:38 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/10 17:01:32 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_token *token)
{
	t_mini	*mini;
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	mini = get_data();
	i = -1;
	if (get_env_part(mini, "PATH") == NULL)
		return (NULL);
	allpath = ft_split(get_env_part(mini, "PATH"), ':');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, token->cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			releaser(allpath);
			return (exec);
		}
		else
			free(exec);
	}
	return (releaser(allpath));
}

int	exec(t_token *token)
{
	char	*path;
	char	**env;
	t_mini	*mini;

	mini = get_data();
	env = env_l_to_dbl_arr(mini->env_test);
	if (token->cmd[0] == NULL)
		return (1);
	if (token->type < 0)
		return (1);
	path = get_path(token);
	if (path == NULL || execve(path, token->cmd, env) < 0)
	{
		command_not_found(token->cmd[0]);
		free_child(token->mini);
		releaser(env);
		free(path);
		exit(0);
	}
		// exit(0);
	return (0);
}

void	wait_pids(t_token *token)
{
	t_token	*head;

	head = token;
	while (head)
	{
		waitpid(head->pid, NULL, 0);
		head = head->next;
	}
}

void	exec_and_stuff(t_token *token)
{
	t_token	*head;
	t_mini	*mini;
	pid_t	pid;

	mini = get_data();
	if (token == NULL)
		return ;
	head = token;
	if (!ft_builtins(head))
	{
		pid = fork();
		if (!pid)
		{
			if (head->type == ABS)
				absolute_path(head);
			else if (head->type == REDIR_IN)
				redir(head);
			else if (head->type == REDIR_OUT)
				redir2(head);
			else if (head->type == REDIR_dbl2)
				heredoc(head);
			else if (head->type == REDIR_dbl)
				redir_append(head);
			else if (head->type == -3)
				do_pipe3(head);
			else if (head->type == PIPE || ft_strncmp(head->next_sep, "|", 1))
				do_pipe(head);
			else if (!ft_strncmp(head->cmd[0], "echo", 5))
			{
				ft_echo(head);
				// exit(0);
			}
			else
				exec(head);
			free_child(token->mini);
			exit(0);
		}
		else
		{
			head = mini->tokens;
			wait_pids(head);
			waitpid(pid, NULL, 0);
			
		}
	}
}
