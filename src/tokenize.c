/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:52:40 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/03 15:35:35 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cmd(t_token *token)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	if (get_env_part(token->mini, "PATH") == NULL)
		return (1);
	allpath = ft_split(get_env_part(token->mini, "PATH"), ':');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, token->cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			releaser(allpath);
			free(exec);
			return (0);
		}
		else
			free(exec);
	}
	releaser(allpath);
	g_errno = 127;
	return (127);
}
int check_file_exists(t_token *token)
{
	if (token->cmd && token->cmd[1] && !is_builtin(token))
	{
		if (token->cmd[1][0] != '-')
		{
			if (access(token->cmd[1], F_OK | X_OK) == 0)
				return 0;
			else
				return 1;
		}
	}
	return g_errno;
}
int get_errno(t_token *token)
{
	if (check_cmd(token))
		g_errno = check_cmd(token);
	
	else if (check_file_exists(token))
		g_errno = 1;
	return g_errno; 
}
t_token	*init_tokens(t_mini *mini, int cmd_index, int x)
{
	t_token	*tokens;
	int		wrd_no;

	wrd_no = 0;
	tokens = malloc(sizeof(t_token) * 100);
	tokens->cmd = malloc(sizeof(char *) * 100);
	if (mini->cmds[cmd_index] && is_sep(mini->cmds[cmd_index]))
	{
		tokens->cmd[wrd_no] = ft_strdup(mini->cmds[cmd_index]);
		cmd_index++;
		wrd_no++;
	}
	while (!is_sep(mini->cmds[cmd_index]) && !is_empty(mini->cmds[cmd_index])
		&& mini->cmds[cmd_index])
	{
		if (!has_quotes(mini->cmds[cmd_index]))
			tokens->cmd[wrd_no] = ft_strdup(mini->cmds[cmd_index]);
		else if (is_quoted(mini->cmds[cmd_index]) == 2)
			tokens->cmd[wrd_no] = ft_strdup2(mini->cmds[cmd_index]);
		else
			tokens->cmd[wrd_no] = ft_strdup2(mini->cmds[cmd_index]);
		wrd_no++;
		cmd_index++;
	}
	tokens->cmd[wrd_no] = NULL;
	tokens->type = 0;
	tokens->pid = -1;
	tokens->token_no = x;
	tokens->env = mini->env_test;
	tokens->mini = mini;
	tokens->next = NULL;
	tokens->errnum = get_errno(tokens);
	return (tokens);
}

void	ft_chain(t_mini *mini, int cmd_index)
{
	int		x;
	t_token	*head;

	x = 1;
	head = mini->tokens;
	if (is_sep(mini->cmds[cmd_index]))
		cmd_index++;
	while (cmd_index < mini->no_wrds || mini->cmds[cmd_index] != NULL)
	{
		if (is_sep(mini->cmds[cmd_index]) && mini->cmds[cmd_index + 1]
			&& cmd_index)
			cmd_index++;
		mini->tokens->next = init_tokens(mini, cmd_index, x++);
		mini->tokens = mini->tokens->next;
		while (mini->cmds[cmd_index] && !is_sep(mini->cmds[cmd_index]))
			cmd_index++;
		if ((mini->cmds[cmd_index]))
			mini->tokens->next_sep = ft_strdup(mini->cmds[cmd_index]);
		else
			mini->tokens->next_sep = NULL;
	}
	mini->tokens = head;
}

int	get_types(t_mini *mini)
{
	t_token	*head;

	head = mini->tokens;
	while (mini->tokens != NULL)
	{
		if (mini->tokens->type >= 0)
		{
			if (mini->tokens->next_sep)
			{
				if (!ft_strncmp(mini->tokens->next_sep, "|", 2))
					mini->tokens->type = PIPE;
				else if (!ft_strncmp(mini->tokens->next_sep, "<<", 3))
					mini->tokens->type = REDIR_dbl2;
				else if (!ft_strncmp(mini->tokens->next_sep, ">>", 3))
					mini->tokens->type = REDIR_dbl;
				else if (!ft_strncmp(mini->tokens->next_sep, ">", 2))
				{
					mini->tokens->type = REDIR_IN;
					if (mini->tokens->next
						&& mini->tokens->next->next_sep == NULL)
						mini->tokens->next->type = -1;
				}
			}
			else
				mini->tokens->type = 1;
			if (!ft_strncmp(mini->tokens->cmd[0], "<", 2))
				mini->tokens->type = REDIR_OUT;
			if (!ft_strncmp(mini->tokens->cmd[0], ">", 2))
			{
				mini->tokens->type = REDIR_IN;
				redir(mini->tokens);
				return (1);
			}
			if (mini->tokens->cmd && (mini->tokens->cmd[0][0] == '.'
					|| mini->tokens->cmd[0][0] == '/'))
				mini->tokens->type = ABS;
		}
		mini->tokens = mini->tokens->next;
	}
	mini->tokens = head;
	return (1);
}

int	tokeniser(t_mini *mini)
{
	int		x;
	t_token	*head;
	int		cmd_index;

	x = 0;
	cmd_index = 0;
	mini->tokens = init_tokens(mini, cmd_index, x);
	head = mini->tokens;
	while (mini->cmds[cmd_index] && !is_sep(mini->cmds[cmd_index]))
		cmd_index++;
	if (mini->cmds[cmd_index] && is_sep(mini->cmds[cmd_index]))
		mini->tokens->next_sep = ft_strdup(mini->cmds[cmd_index]);
	else
		mini->tokens->next_sep = NULL;
	ft_chain(mini, cmd_index);
	mini->tokens = head;
	releaser(mini->cmds);
	if (!get_types(mini))
		return (0);
	return (1);
}
