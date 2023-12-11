/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:01:40 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/11 18:58:06 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

int	set_shlvl(void)
{
	char	*cur_shlvl;
	int		sh_lvl;
	char	*shlvl;
	char	*new_SHLVL;
	t_mini	*mini;

	mini = get_data();
	shlvl = ft_strdup("SHLVL");
	cur_shlvl = get_env_part(mini, shlvl);
	if (cur_shlvl == NULL)
		return (0);
	sh_lvl = ft_atoi(cur_shlvl);
	sh_lvl++;
	new_SHLVL = (ft_itoa(sh_lvl));
	update_env_part(mini, shlvl, new_SHLVL);
	new_SHLVL = ft_free(new_SHLVL);
	free(shlvl);
	return (1);
}

t_mini	*get_data(void)
{
	static t_mini	*mini;

	if (!mini)
	{
		mini = ft_calloc(1, sizeof(t_mini));
		if (!mini)
			return (NULL);
		return (mini);
	}
	return (mini);
}

void	*releaser(char **table)
{
	int	i;

	i = 0;
	if (table)
	{
		while (table[i])
		{
			free(table[i]);
			i++;
		}
		free(table);
	}
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
	// print_token(mini);
	init_signals(CHILD);
	exec_and_stuff(mini->tokens);
	wait_pids(mini->tokens);
	wait_c_pids(mini->tokens);
	free_tokens(mini->tokens);
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
				if (parsing == -1)
					ft_putendl_fd("exit", 2);
				free(mini->input);
				free_minishell(mini);
				return (g_errno);
			}
			else if (parsing > 0){

				run_minishell(mini);
			
			}
			// reset_minishell(mini);
		}
	}
	return (g_errno);
}
