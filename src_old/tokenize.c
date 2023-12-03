/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:28:34 by alpicard          #+#    #+#             */
/*   Updated: 2023/10/17 07:39:10 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_token(t_mini *mini)
{
	int		x;
	t_token	*head;

	x = 0;
	head = mini->tokens;
	while (head != NULL)
	{
		ft_printf("token %d: type: %d\n", head->token_no, head->type);
		display_split(head->cmd, "\tcmd");
		ft_printf("\nnext sep: %s\n", mini->tokens->next_sep);
		head = head->next;
	}
}

t_token	*init_token(t_mini *mini, char *s_cmd, int x)
{
	t_token	*token;
	int wrd_count = 0;
	token = malloc(sizeof(t_token *) * no_of_words(mini->input) + 1);
	token->token_no = x + 1;
	token->type = x;
	token->cmd = malloc(sizeof(char *));
	token->cmd = mini_split(s_cmd);
	while (token->cmd[wrd_count] != 0)
		wrd_count++;
	mini->cmd_wrd_no += wrd_count; 
	token->next_sep = NULL;
	token->input = STDIN;
	token->output = STDOUT;
	token->next = NULL;

	return (token);
}

int	tokenize(t_mini *mini)
{
	int x;
	x = 0;
	char **sp_sep;
	t_token *head;
	sp_sep = ft_split2(mini->input, "|><");
	display_split(sp_sep, "sp_sep");
	while (sp_sep[x])
		x++;
	mini->no_sep = x - 1;
	x = 0;
	mini->tokens = init_token(mini, sp_sep[x], x);
	if (mini->no_sep >= 1)
	{
		head = mini->tokens;
		while (sp_sep[x] && mini->tokens != NULL)
		{
			if (sp_sep[x + 1] != 0)
			{
				mini->tokens->next = init_token(mini, sp_sep[x + 1], x + 1);
				mini->tokens = mini->tokens->next;
			}
			x++;
		}
		mini->tokens = head;
	}
	if (mini->tokens->cmd[0] == NULL)
	{
		mini->tokens->cmd = mini->cmds;
		mini->tokens->type = -1;
	}
	releaser(sp_sep);
	return (1);
}