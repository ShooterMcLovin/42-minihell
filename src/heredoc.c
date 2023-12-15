/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:36:18 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/14 18:26:37 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**build_heredoc_cmd2(t_token *token)
{
	char	**cmd;
	int i = 0;
	int cmd_no;

	cmd_no = 0;
	cmd = malloc(sizeof(char *) * 15);
	if (!ft_strncmp(token->cmd[i], "ls", 3))
		cmd_no++;
	while (token->cmd[cmd_no])
		cmd[i++] = (token->cmd[cmd_no++]);
	cmd[i] = (".temp");
	cmd[i + 1] = NULL;
	return (cmd);
}

int	do_heredoc(t_token *token)
{
	char	**here_doc_cmd;
	char	*path;
	char	**env;

	here_doc_cmd = build_heredoc_cmd2(token);
	env = env_l_to_dbl_arr(token->env);
	path = get_path(token);
	if (is_sep(here_doc_cmd[0]))
		return (1);
	if ((execve(path, here_doc_cmd, env) < 0))
	{
		free(here_doc_cmd);
		close(token->fd_hd);
		command_not_found(token->cmd[0]);
		close(token->fd_hd);
		path = NULL;
		releaser(env);
	}
	return (0);
}

int	heredoc(t_token *token)
{
	char	*delimiter;
	char	*heredoc_input;

	if (!token->next->cmd[0])
		return (syntax_error());
	delimiter = ft_strdup(token->next->cmd[0]);
	token->fd_hd = open(".temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	heredoc_input = get_prompt(HEREDOC);
	if (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1))
		ft_putendl_fd(heredoc_input, token->fd_hd);
	while (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1))
	{
		heredoc_input = get_prompt(HEREDOC);
		if (ft_strncmp(heredoc_input, delimiter, ft_strlen(delimiter) + 1))
			ft_putendl_fd(heredoc_input, token->fd_hd);
	}
	free(delimiter);
	if (token->next && token->next->type == PIPE)
		do_pipe3(token);
	else
		do_heredoc(token);
	close(token->fd_hd);
	return (1);
}
