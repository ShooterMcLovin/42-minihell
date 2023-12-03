/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:39:24 by alpicard          #+#    #+#             */
/*   Updated: 2023/10/01 13:43:23 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	get_paths(t_minishell *minishell)
{
	int	x;

	x = 0;
	while (ft_strncmp(minishell->env[x], "PATH=", 5))
		x++;
	minishell->paths = ft_split(&(minishell->env[x])[5], ':');
}

static void	*release(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *input;
	t_minishell minishell;

	if (ac > 1)
		return (0);
	// minishell.env = env;
	//While 1 ???
	while (1)
	{
		input = readline("Minishell-1.0$ ");
		if (!parser(input, &minishell))
		{
			ft_printf("Custom Exit: Parsing Fail // Empty Input\n");// replace by parser fail
			free(input);
			add_history(input);
			return (0) ; /// remove
		}
		if (!ft_strncmp(minishell.tokens->line, "echo", 5))
			ft_echo(&minishell, &minishell.split_input[1]);
		if (!ft_strncmp(minishell.tokens->line, "pwd", 3)) 
			ft_pwd();
		if (!ft_strncmp(minishell.tokens->line, "PWD", 3))
			ft_pwd();

		free_tokens(minishell.tokens);
		release(minishell.split_input);
		add_history(input);
		// Do stuff...
		free(input);
	}
	return (0);
}