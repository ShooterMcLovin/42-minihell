/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:09:36 by alpicard          #+#    #+#             */
/*   Updated: 2023/10/01 13:48:41 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

/*
The Command Table
The Command Table is an array of  SimpleCommand structs. 
A SimpleCommand struct contains members for the command and arguments of a 
single entry in the pipeline. The parser will look also at the command line 
and determine if there is any input or output redirection based on symbols 
present in the command (i.e. < infile, or > outfile).   
*/
/*
Your shell must implement the following builtins:
	echo with option -n
	cd with only a relative or absolute path
	pwd with no options
	export with no options
	unset with no options
	env with no options or arguments
	exit with no options
*/

int	get_type(char *input)
{
	if (!input[0])
		return (EMPTY);
	if (ft_strchr("<", input[0]))
		return (REDIR_IN);
	if (ft_strchr(">", input[0]))
		return (REDIR_OUT);
	if (ft_strchr("|", input[0]))
		return (PIPE);
	else
		return (ARGS);
}

t_token	*next_token(int *i, t_minishell *mini)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (*i == 0)
	{
		token->type = CMD;
		token->line = mini->split_input[(*i)++];
	}
	else
	{
		token->line = mini->split_input[(*i)++];
		token->type = get_type(token->line);
	}
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*init_tokens(t_minishell *mini, char *input)
{
	t_token	*tkn;
	t_token	*head;
	int		x;

	x = 0;
	tkn = next_token(&x, mini);
	head = tkn;
	while (x < mini->no_words && input[x])
	{
		tkn->next = next_token(&x, mini);
		tkn = tkn->next;
	}
	tkn = head;
	return (tkn);
}

int	wrd_counter(t_minishell *mini, char **input)
{
	int	no_wrds;

	no_wrds = 0;
	while (mini->split_input[no_wrds] != NULL)
	// && mini->split_input[no_wrds][0] != '<'
	// && mini->split_input[no_wrds][0] != '>'
	// && mini->split_input[no_wrds][0] != '|')
	{
		no_wrds++;
	}
	if (no_wrds == 0)
		return (0);
	mini->no_words = no_wrds;
	return (no_wrds);
}

int	parser(char *input, t_minishell *mini)
{
	t_token	*head;
	int		no_wrds;

	mini->split_input_temp = ft_split(input, '"');
	mini->split_input = ft_split(input, ' ');
	no_wrds = wrd_counter(mini, &mini->split_input[no_wrds]);
	mini->tokens = init_tokens(mini, input);
	if (mini->tokens == NULL || !mini->tokens->line) // return 0 if empty
		return (0);
	print_tokens(mini);
	return (1);
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

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens->next;
		free(tokens);
		tokens = temp;
	}
}

void	print_tokens(t_minishell *mini)
{
	t_token	*head;

	head = mini->tokens;
	while (head != NULL)
	{
		// if (head->type == PIPE && head->next != NULL)
		// 	head->next->type = CMD;
		// else if (head->type == REDIR_OUT && head->next)
		// 	head->next->type = FILE;
		// else if (head->type == CMD && head->next->type == REDIR_IN
		// 		&& head->next != NULL)
		// 	head->type = FILE;
		// else if (head->type == REDIR_IN && head->next)
		// 	head->next->type = CMD;
		printf("line: %s, type:%d\n", head->line, head->type);
		head = head->next;
	}
}

// int	main(int ac, char **av)
// {
// 	t_minishell	mini;

// 	if (ac > 1)
// 	{
// 		parser(av[1], &mini);
// 		if (!ft_strncmp(mini.tokens->line, "echo", 5))
// 			ft_echo(&mini, &mini.split_input[1]);
// 		free_tokens(mini.tokens);
// 		release(mini.split_input);
// 	}
// }
// int	malloc_count(char *input_line)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**input;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	input = ft_split(input_line, ' ');
// 	while (input[i])
// 	{
// 		j = 0;
// 		while (input[i][j])
// 		{
// 			j++;
// 			k++;
// 		}
// 		i++;
// 	}
// 	j = 0;
// 	while (input[j])
// 		free(input[j++]);
// 	free(input);
// 	return (i + k);
// }

// char	*ignore_spaces(char *line, t_minishell *mini) // removes extra spaces
// {
// 	char *input;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	if (!line)
// 		return (NULL);
// 	j = malloc_count(line); // malloc bonne longueur (incl \0)
// 	input = malloc(j);
// 	i = 0;
// 	j = 0;
// 	while (line[i] == ' ')
// 		i++;
// 	while (line[i] != '\0')
// 	{
// 		if ((line[i] == ' ' && (line[i + 1] != ' ' && line[i + 1] != '\0')
// 				|| line[i] != ' '))
// 			input[j++] = line[i];
// 		i++;
// 	}
// 	input[j] = 0;
// 	return (input);
// }