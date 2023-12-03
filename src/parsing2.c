/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:04:07 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/02 14:22:34 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_dollar	*ft_dol(void)
{
	t_dollar	*dol;
	int			buff_size;

	buff_size = 100;
	dol = malloc(sizeof(t_dollar));
	if (!dol)
		return (0);
	dol->part = malloc(buff_size);
	dol->start_of_cmd = malloc(buff_size);
	dol->dollar = malloc(buff_size);
	dol->cmd = malloc(buff_size);
	return (dol);
}

char	*dollar_sign(t_mini *mini, int cmd_no)
{
	int			x;
	int			i;
	int			j;
	t_dollar	*dol;
	
	i = 0;
	j = 0;
	dol = ft_dol();
	x = has_dollar_sign(mini->cmds[cmd_no]);
	if (mini->cmds[cmd_no][i] == 34 || mini->cmds[cmd_no][i] == 39)
		i++;
	if (mini->cmds[cmd_no][i + 1] == '?')
	{
		// ft_printf("<%s>\n", &(mini->cmds[cmd_no][i]));
		return (ft_itoa(g_errno));
	}
	else
	{
		while (i < x && mini->cmds[cmd_no][i] != '$')
			dol->start_of_cmd[j++] = mini->cmds[cmd_no][i++];
		if (mini->cmds[cmd_no][++x])
		{
			dol->part = check_part((&mini->cmds[cmd_no][x]));
			dol->dollar = ft_strdup(get_env_part(mini, dol->part));
			if (!dol->dollar)
				dol->dollar = ft_strdup("\0");
		}
		dol->cmd = ft_strjoin(dol->start_of_cmd, dol->dollar);
		if (dol->dollar)
			dol->cmd = ft_strjoin(dol->cmd, &mini->cmds[cmd_no][x + ft_strlen(dol->part)]);
	// free(dol->cmd);
	free(dol->part);
	free(dol->start_of_cmd);
	free(dol->dollar);

	return (dol->cmd);
	}
}

int	has_dollar_sign(char *input)
{
	int	i;

	i = 0;
	if (!input || !input[0])
		return (0);
	while (input[i])
	{
		if (input[i] == '$')
			return (i);
		i++;
	}
	return (0);
}
