/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:34:54 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/03 16:00:41 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void	do_pipe(t_token *token)
{
	pid_t	pid;

	if (is_empty(token->next->cmd[0]))
		return ;
	if (pipe(token->p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(token->p_fd[0]);
		dup2(token->p_fd[1], 1);
		close(token->p_fd[1]);
		exec(token);
		exit(0);
	}
	else
	{
		token->pid = pid;
		close(token->p_fd[1]);
		dup2(token->p_fd[0], 0);
		close(token->p_fd[0]);
		exec_and_stuff(token->next);
		// exit(0);
	}
}
void	do_pipe2(t_token *token)
{
	pid_t	pid;
	int		p_fd[2];

	if (is_empty(token->next->cmd[0]))
		return ;
	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (token->pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(token);
	}
	else
	{
		token->pid = pid;
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		if (token->next->next->cmd)
			exec(token->next->next);
		// exec(token);
	}
}
void	do_pipe3(t_token *token)
{
	pid_t	pid;
	int		p_fd[2];
	char	*path;
	char	**here_doc_cmd;

	if (is_empty(token->next->cmd[0]))
		return ;
	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		path = get_path(token);
		here_doc_cmd = build_heredoc_cmd2(token);
		if (execve(path, here_doc_cmd,
				env_l_to_dbl_arr(token->mini->env_test)) < 0)
			command_not_found(token->cmd[0]);
		exit(0);
	}
	else
	{
		token->pid = pid;
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		if (token->next->next)
			exec_and_stuff(token->next->next);
		// exec(token->next->next);
		waitpid(token->pid, 0, 0);
		// exec(token);
	}
}
