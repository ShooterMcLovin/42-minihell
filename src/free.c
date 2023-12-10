/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:13:03 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/10 12:33:03 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens->next;
		releaser(tokens->cmd);
		free(tokens->next_sep);
		if (tokens->fd_out)
			close(tokens->fd_out);
		// free_env(tokens->env);
		free(tokens);
		tokens = temp;
	}
	// free(tokens);
}

void	free_env(t_environ *env)
{
	t_environ	*temp;

	while (env != NULL)
	{
		temp = env->next;
		free(env->env_var);
		free(env->env_val);
		// releaser(env->temp);
		free(env);
		env = temp;
	}
	free(env);
}

void	free_export(t_export *exp)
{
	t_export	*temp;

	while (exp != NULL)
	{
		temp = exp->next;
		free(exp->env_val);
		free(exp->env_var);
		releaser(exp->temp);
		free(exp);
		exp = temp;
	}
	free(exp);
}

int	free_minishell(t_mini *mini)
{
	int	err_no;

	err_no = mini->errno;
	free_env(mini->env_test);
	mini->env = NULL;
	if (mini->tokens)
		free_tokens(mini->tokens);
	free(mini->SHLVL);
	// free(mini->PATH);
	free(mini);
	// free(mini->input);
	return (err_no);
}

void free_child(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(mini->tokens);
	free_env(mini->env_test);
	free(mini);
	
}

void	reset_minishell(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(mini->tokens);
	// free_env(mini->env_test);
	// free(mini);
	// mini = get_data();
	// set_env(mini, env);
}
