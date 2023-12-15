/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:01:40 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/14 19:02:20 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

void	*releaser(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
	return (NULL);
}

int	init_minishell(char **env)
{
	t_mini	*mini;

	mini = get_data();
	mini->env = env;
	mini->cmds = NULL;
	set_env(mini, env);
	set_shlvl();
	update_env_part(mini, "OLDPWD", "/");
	return (1);
}

char	*get_prompt(char *prt)
{
	char	*line;

	line = readline(prt);
	if (line)
	{
		add_history(line);
		return (line);
	}
	return (NULL);
}

void	run_minishell(t_mini *mini)
{
	print_token(mini);
	init_signals(CHILD);
	exec_and_stuff(mini->tokens);
	wait_pids(mini->tokens);
	wait_c_pids(mini->tokens);
	// free(mini->tokens);
	free(mini->input);
	// free_minishell(mini);
	free_tokens(mini->tokens);
	// free_child(mini);
}

int	main(int ac, char **av, char **env)
{
	static t_mini	*mini;
	int				parsing;

	(void)av;
	if (ac > 1)
		return (0);
	mini = get_data();
	g_errno = 0;
	init_minishell(env);
	while (1)
	{
		init_signals(INTERACTIVE);
		mini->input = get_prompt(PROMPT);
		if (!is_empty(mini->input))
		{
			parsing = ft_parse(mini);
			if (parsing < 0)
			{
				if (parsing == -1){

					ft_putendl_fd("exit", 2);
					free(mini->input);
					free_minishell(mini);
				}
				return (g_errno);
			}
			else if (parsing > 0)
				run_minishell(mini);
		}
	}
	return (g_errno);
}

/*Errors
builtins
besoin de exit ++

exit 6 
senser donne le 6 quand tu fait echo $?
donne pas 0 si la commande a fonctionnner tjrs 127

signaux heredoc
*/

/*LEAKS
encore des leaks dans export
	definitely lost: 41 bytes in 2 blocks
	indirectly lost: 15 bytes in 2 blocks
leaks dans unset aussi
	2 block de plus dans indirectly
echo $PATH
	2 leaks
exit 1 1 1 1 leaks on peu le bloquer
	si il y as plus que 1 chiffre"arguments" ca leaks sinon non
*/






