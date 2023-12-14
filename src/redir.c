/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:00:20 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/13 21:39:14 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

int token_size(t_token *token)
{
	int size;

	size = 0;
	while (token->cmd[size])
		size++;
	return size;
}


char	**build_redir_cmd(t_token *token)
{
	char	**cmd;
	int cmd_no;
	int cmd_index;

	cmd_no = 0;
	cmd_index = 0;
	cmd = malloc(sizeof(char *) * token_size(token));
	while (token->cmd[cmd_no])
		cmd[cmd_index++] = token->cmd[cmd_no++];
	cmd[cmd_index] = NULL;
	return (cmd);
}

void	redir(t_token *token)
{
	t_token	*temp;
	char *path;
	char **cmd;
	char **env;
	temp = token;
	if (token->type == REDIR_IN)
	temp->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
	else
		token->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_APPEND,
			0777);
	dup2(temp->fd_out, 1);
	if (temp->fd_out < 0)
		return ;
	path = get_path(token);
	cmd = build_redir_cmd(token);
	env = env_l_to_dbl_arr(token->mini->env_test);
	if (token->next->next_sep && token->next->next_sep[0] == '|')
		do_pipe2(token);
	else{

	if ((execve(path, cmd, env) < 0))
	{
		free(cmd);
		command_not_found(token->cmd[0]);
		close(token->fd_hd);
		path = NULL;
		releaser(env);
	}
	}
}