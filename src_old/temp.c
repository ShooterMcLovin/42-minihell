/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:20:40 by alpicard          #+#    #+#             */
/*   Updated: 2023/10/01 13:41:57 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int check_quotes(char *input)
{
	int i = 0;
	int j = 0;
	if (!input || !input[0])
		return(-1);
	while (input[i])
	{
		if (input[i] == '"')
			j++;
		i++;
	}
	if (j % 2 == 0 && j > 0)
		return (j);
	else
	 	return (0-j);
}

// void split_quotes(char *input)
// {
// 	char **split;
// 	int x = 0;
// 	// if (check_quotes(input))
// 		split = ft_split(input, 34);
	
// 	while (split[x])
// 		ft_printf(":%s:\n", split[x++]);
// }

// int main(int ac, char **av)
// {
// 	if (ac > 1)
// 		split_quotes(av[1]);
// }