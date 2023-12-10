/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:00:20 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/10 13:30:02 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redir(t_token *token)
{
	t_token	*temp;

	temp = token;
	if (token->cmd && token->cmd[0][0] == '>')
	{
		token->fd_out = open(token->cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		return ;
	}
	while (token->next && token->next->type == 4)
	{
		temp->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
		token = token->next;
	}
	if (token->next)
	{
		temp->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
		dup2(temp->fd_out, 1);
	}
	if (temp->fd_out < 0)
		return ;
	exec(temp);
	// if (token->next->type > 0)
	// else
	// exec_and_stuff(token->next);
}

void	redir2(t_token *token)
{
	if (token->cmd[1])
		token->fd_in = open(token->cmd[1], O_RDONLY, 0777);
	if (token->fd_in <= 0)
	{
		ft_putstr_fd("No such file dumbass\n", 2);
		// exit(0);
	}
	if (token->next_sep && token->next_sep[0] == '|')
	{
		do_pipe(token);
	}
	dup2(token->fd_in, 0);
	if (token->next->type == PIPE)
		do_pipe2(token);
	else
		exec(token);
}

char	**build_heredoc_cmd2(t_token *token)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = (token->cmd[0]);
	if (!ft_strncmp(cmd[0], "ls", 3))
	 	cmd[1] = NULL;
	else
		cmd[1] = (".temp");
	cmd[2] = NULL;
	return (cmd);
}

int	heredoc(t_token *token)
{
	char	*delimiter;
	char	*heredoc_input;
	char	**here_doc_cmd;
	char	*path;
	char **env;

	if (!token->next->cmd[0])
		return (syntax_error());
	delimiter = ft_strdup(token->next->cmd[0]);
	token->fd_hd = open(".temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	heredoc_input = get_prompt(HEREDOC);
	if (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1 ))
			ft_putendl_fd(heredoc_input, token->fd_hd);
	while (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1))
	{
		heredoc_input = get_prompt(HEREDOC);
		if (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1 ))
			ft_putendl_fd(heredoc_input, token->fd_hd);
	}
	free(delimiter);
	if (token->next && token->next->type == PIPE)
		do_pipe3(token);
	else
	{
		here_doc_cmd = build_heredoc_cmd2(token);
		env = env_l_to_dbl_arr(token->env);
		path = get_path(token);
		if ((execve(path, here_doc_cmd, env) < 0))
			command_not_found(token->cmd[0]);
		releaser(here_doc_cmd);
		free(path);
		releaser(env);
	}
	return 1;
}

void	redir_append(t_token *token)
{
	token->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_APPEND,
			0777);
	dup2(token->fd_out, 1);
	exec(token);
}
