/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:14:32 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/10 13:38:48 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

void	ft_int_handler(int sig)
{
	(void)sig;

	ft_putstr_fd("\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
void	ft_quit_handler2(int sig)
{
	(void)sig;
	// printf("^\\Quit\n");
	kill(0,0);
 
}
void	ft_int_handler2(int sig)
{
	(void)sig;
	ft_putstr_fd("^C\n",1);
	rl_on_new_line();

	kill(0,0);
}

void init_signals(int mode)
{
	if (mode == INTERACTIVE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_int_handler);

	}
	else if (mode == CHILD){
		signal(SIGQUIT, &ft_quit_handler2);
		signal(SIGINT, &ft_int_handler2);
	}
}
/* Authorized func
	readline();
	rl_clear_history();
	rl_on_new_line();
	rl_replace_line();
 	rl_redisplay(); 
 	add_history()
	*/




// // Handles interupt signal "^C" while programs are running
// void	sigint_runtime(int signum)
// {
// 	(void)signum;
// 	kill(0, 0);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	rl_on_new_line();
// 	return ;
// }

// // Handles quit signal "^\" while programs are running
// void	sigquit_runtime(int signum)
// {
// 	t_data	*data;

// 	data = get_data();
// 	(void)signum;
// 	kill(0, 0);
// 	ft_putstr_fd("Quit: ", STDOUT_FILENO);
// 	ft_putnbr_fd(data->exit_status, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	rl_on_new_line();
// 	return ;
// }