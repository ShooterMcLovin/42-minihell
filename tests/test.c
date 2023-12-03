/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:57:46 by alpicard          #+#    #+#             */
/*   Updated: 2023/11/19 18:51:56 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../include/minishell.h"
#include "../libft/include/libft.h"

void	*releaser(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return (NULL);
}

void	display_split(char **s, char *str)
{
	int	x;

	x = 0;
	if (str == 0)
		str = "split";
	if (s[0] == NULL)
		ft_printf("\nCMD Empty\n");
	while (s[x])
	{
		ft_printf("%s[%d]<%s>\n", str, x, s[x]);
		x++;
	}
}

void print_real_env(char **env)
{
	int x = -1;
	while (env[++x])
		printf("%s\n", env[x]);
}

void print_env(t_environ *environ)
{
	t_environ *head;
	head = environ;
	while (head)
	{
		ft_printf("[%d]%s = %s\n",head->num, head->env_var, head->env_val);
		head = head->next;
	}
}

t_environ *init_item(char *to_split)
{
	t_environ *env;
	char **temp;
	temp = ft_split(to_split, '=');
	env = malloc(sizeof(t_environ *));
	if (!temp || !env)
	 return NULL;
	if (temp[0]){
		env->env_var = malloc(ft_strlen(temp[0]));
		env->env_var = ft_strdup(temp[0]);

	}
	if (temp[1]){

		env->env_val = malloc(ft_strlen(temp[1]));
		env->env_val = ft_strdup(&to_split[ft_strlen(env->env_var) + 1]);
	}

	env->next = NULL;
	return env;
}

t_environ *set_env(char **env)
{
	// display_split(env, "env:");
	t_environ *environ;
	int x = 0;
	t_environ *head;
	environ = init_item(env[x]);
	environ->num = x;
	head = environ;
	while (env[++x])
	{
		environ->next = init_item(env[x]);
		environ->next->num = x;
		environ = environ->next;
	}
	return(head);
}

int main(int ac ,char **av, char **env)
{
	t_environ *environ = set_env(env);
	print_env(environ);
	print_real_env(env);
}