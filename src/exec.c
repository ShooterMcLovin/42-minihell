/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:35:38 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/11 19:10:58 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>

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

void	exec_fail(t_token *token, char *path, char **env)
{
	command_not_found(token->cmd[0]);
	free_child(token->mini);
	releaser(env);
	free(path);
	exit(0);
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
	if (is_sep(token->cmd[0]))
		exec_fail(token, path, env);
	if (path == NULL || execve(path, token->cmd, env) < 0)
		exec_fail(token, path, env);
	return (0);
}

void	wait_pids(t_token *token)
{
	t_token	*head;

	head = token->mini->tokens;
	while (head)
	{
		if(head->pid)
			waitpid(head->pid, NULL, 0);
		head = head->next;
	}
}

void	wait_c_pids(t_token *token)
{
	t_token	*head;

	head = token->mini->tokens;
	while (head)
	{
		if(head->child_pid)
			waitpid(head->child_pid, NULL, 0);
		head = head->next;
	}
}

void	do_child_stuff(t_token *token)
{
	if (token->type == ABS)
		absolute_path(token);
	else if (token->type == REDIR_IN)
		redir(token);
	else if (token->type == REDIR_OUT)
		redir2(token);
	else if (token->type == REDIR_DBL2)
		heredoc(token);
	else if (token->type == REDIR_DBL)
		redir_append(token);
	else if (token->type == -3)
		do_pipe3(token);
	else if (token->type == PIPE || ft_strncmp(token->next_sep, "|", 1))
		do_pipe(token);
	else if (!ft_strncmp(token->cmd[0], "echo", 5))
		ft_echo(token);
	else if (!ft_strncmp(token->cmd[0], "pwd", 4))
		ft_pwd(token);
	else
		exec(token);
	free_child(token->mini);
	exit(0);
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
			do_child_stuff(head);
		else
		{
			token->pid = pid;
				// wait_pids(mini->tokens);
				// wait_c_pids(mini->tokens);
			// wait(0);
			wait_pids(mini->tokens);
			// waitpid(pid,0,0);
			
		}
	}
	
}
