/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:34:52 by alpicard          #+#    #+#             */
/*   Updated: 2023/11/19 19:50:47 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// t_env	*init_env_list(t_mini *mini, int env_item)
// {
// 	t_env	*env;

// 	env = malloc(sizeof(t_env *));
// 	if (mini->env[env_item])
// 		env->content = ft_strdup(mini->env[env_item]);
// 	else
// 		env->content = NULL;
// 	env->next = NULL;
// 	return (env);
// }

// t_environ	*new_env_list(char *content)
// {
// 	t_environ	*env;
// 	char **split;
// 	split = ft_split(content, '=');
// 	if (content)
// 	{
// 		env = malloc(sizeof(t_env *));
// 		env->env_var = ft_strdup(split[0]);
// 		env->env_val = ft_strdup(split[1]);
// 		env->next = NULL;
// 		return (env);
// 	}
// 	return (NULL);
// }


// void	env_list(t_mini *mini)
// {
// 	t_env	*head;
// 	int		env_item;

// 	env_item = 0;
// 	mini->env_l = init_env_list(mini, env_item);
// 	head = mini->env_l;
// 	while (++env_item < mini->env_len)
// 	{
// 		mini->env_l->next = init_env_list(mini, env_item);
// 		mini->env_l = mini->env_l->next;
// 	}
// 	mini->env_l = head;
// }

// int	ft_set_env(t_mini *mini, char **env)
// {
// 	int	x;
// 	int	env_item;

// 	x = 0;
// 	env_item = 0;
// 	while (env[x])
// 		x++;
// 	mini->env_len = x;
// 	mini->env = malloc(sizeof(char *) * x + 10); // room for 10 export
// 	while (env_item < x)
// 	{
// 		mini->env[env_item] = ft_strdup(env[env_item]);
// 		env_item++;
// 	}
// 	env_list(mini);
// 	return (1);
// }
