/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:45:24 by siroulea          #+#    #+#             */
/*   Updated: 2023/12/13 12:46:08 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redir_append(t_token *token)
{
	token->fd_out = open(token->next->cmd[0], O_WRONLY | O_CREAT | O_APPEND,
			0777);
	dup2(token->fd_out, 1);
	exec(token);
}
