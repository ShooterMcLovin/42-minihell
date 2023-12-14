/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:09:24 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/13 20:39:40 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	do_child_stuff(t_token *token)
{

	if (token->type == PIPE || ft_strncmp(token->next_sep, "|", 1))
		do_pipe(token);
	else if (token->type == ABS)
		absolute_path(token);
	else if (token->type == -3)
		do_pipe3(token);
	else
		exec(token);
	// free_child(token->mini);
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
	pid = fork();

	if (!pid)
	{
		if (head->type == REDIR_OUT)
			redir2(head);
		else if (token->type == REDIR_IN)
			redir(token);
		else if (token->type == REDIR_DBL)
			redir(token);
		else if (token->type == REDIR_DBL2)
			heredoc(token);
		else if (is_builtin(token))
			ft_builtins(token);
		else
			do_child_stuff(head);
	}
	else
	{
		head->child_pid = pid;
		wait_pids(mini->tokens);
	}
	
}
