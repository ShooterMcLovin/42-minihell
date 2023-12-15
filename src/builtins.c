/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 08:34:53 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/15 12:18:50 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_pwd(t_token *token)
{
	char	cur_dir[100];

	getcwd(cur_dir, 100);
	free(token->cmd[0]);
	token->cmd[0] = ft_strdup(cur_dir);
	ft_putendl_fd(cur_dir, 1);
	return (1);
}

int	ft_echo(t_token *token)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	if (!token->cmd[1] || token->cmd[1] == NULL)
	{
		write(1, "\n", 1);
		return (1);
	}
	if (token->cmd[i] && !ft_strncmp(token->cmd[i], "-n", 2))
	{
		n_option = 1;
		i++;
	}
	while (token->cmd[i])
	{
		ft_putstr_fd(token->cmd[i], 1);
		if (token->cmd[i + 1] && token->cmd[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (1);
}

int	ft_unset(t_token *token)
{
	t_mini * mini;
	char		**part;
	int			unset_no;
	int			cmd_no;
	int			len;
	t_environ	*head;

	unset_no = 0;
	cmd_no = 0;
	mini = get_data();
	if (!token->cmd[1] || !token->cmd[1][0])
		return (0);
	part = malloc(token_size(token));
	head = mini->env_test;
	while (token->cmd[++cmd_no])
	{
		part[unset_no] = (token->cmd[cmd_no]);
		len = ft_strlen(part[unset_no]);
		while (mini->env_test->next && ft_strncmp(part[unset_no],
				mini->env_test->next->env_var, len) != 0)
			mini->env_test = mini->env_test->next;
		if (mini->env_test->next != NULL)
		{
			free(mini->env_test->next->env_var);
			mini->env_test->next = mini->env_test->next->next;
		}
		mini->env_len--;
		unset_no++;
	}
	// releaser(part);
	mini->env_test = head;
	return (0);
}

int	ft_builtins(t_token *token)
{
	if (!ft_strncmp(token->cmd[0], "PWD", 3))
		ft_pwd(token);
	if (!ft_strncmp(token->cmd[0], "pwd", 3))
		ft_pwd(token);
	if (!ft_strncmp(token->cmd[0], "echo", 3))
		ft_echo(token);

	else if (!ft_strncmp(token->cmd[0], "env", 3))
		ft_env(token);
	exit(0); //empeche export si unmute
	// waitpid(token->child_pid,0,0);
	return (1);
}
