/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:54:39 by alpicard          #+#    #+#             */
/*   Updated: 2023/10/21 13:54:56 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*user_input;

	// Initialize readline
	rl_initialize();
	rl_readline_name = "YourAppName";
	while (1)
	{
		user_input = rl_readline("Enter your command: ");
		if (user_input == NULL)
		{
			break ; // User pressed Ctrl+D
		}
		// Redisplay prompt with a new prompt
		rl_set_prompt("New prompt: ");
		// Process the user's input here
		add_history(user_input);
		free(user_input);
	}
	return (0);
}
