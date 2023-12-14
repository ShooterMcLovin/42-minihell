/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:33:40 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/13 20:38:22 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	tokens_next_sep(t_token *tokens)
{
	if (!ft_strncmp(tokens->next_sep, "|", 2))
		tokens->type = PIPE;
	else if (!ft_strncmp(tokens->next_sep, "<<", 3))
		tokens->type = REDIR_DBL2;
	else if (!ft_strncmp(tokens->next_sep, ">>", 3))
		tokens->type = REDIR_DBL;
	else if (!ft_strncmp(tokens->next_sep, ">", 2))
		tokens->type = REDIR_IN;
	else if (!ft_strncmp(tokens->next_sep, "<", 2))
		tokens->type = REDIR_OUT;
	
}

void	token_type(t_token *tokens)
{
	if (tokens->next_sep)
		tokens_next_sep(tokens);
	else
		tokens->type = 1;
	// else if (tokens->cmd && (tokens->cmd[0][0] == '.'
	// 	|| tokens->cmd[0][0] == '/'))
	// 	tokens->type = ABS;
}

int	get_types(t_mini *mini)
{
	t_token	*head;

	head = mini->tokens;
	while (mini->tokens != NULL)
	{
		if (mini->tokens->next_sep)
			tokens_next_sep(mini->tokens);
		else
			mini->tokens->type = 1;
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
