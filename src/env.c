/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 08:06:25 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/14 19:02:54 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_token *token)
{
	t_mini *mini;
	(void)token;
	mini = get_data();
	print_env(mini->env_test);
	return (1);
}

void	ft_envadd_back(t_environ **env, t_environ *neo)
{
	t_environ	*temp;

	if (*env == NULL)
		*env = neo;
	else
	{
		temp = ft_envlast(*(env));
		temp->next = neo;
	}
}

t_environ	*ft_envlast(t_environ *env)
{
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (env);
}
