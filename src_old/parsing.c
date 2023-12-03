/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:59:47 by alpicard          #+#    #+#             */
/*   Updated: 2023/10/13 08:21:03 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_empty(char *input)
{
	int i = 0;
	if (!input || !input[0])
		return 1;
	while(input[i] && input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return 1;
	return 0;
}

int ft_parse(t_mini *mini)
{	

	mini->cur_sent = 0;
	mini->no_wrds = no_of_words(mini->input);
	mini->cmds = malloc(sizeof(char *) * mini->no_wrds + 1);
	mini->cmds = mini_split(mini->input); /// mini.cmds to do stuff
	return (1);
}
// void split_quotes(t_mini *mini)
// {
// 	int index = 0;// index == i if not at begining
// 	mini->sp_quotes = malloc(100 * 100); 
// 	if (!mini->sp_quotes)
// 		return ;
// 	while (mini->sp_pipes[index])//input[0] == **split on quotes
// 	{
// 		mini->sp_quotes[index]= ft_split(mini->sp_pipes[index], 34);
// 		index++;
// 	}
// }

// void split_pipes(t_mini *mini) // split on sep??
// {
// 	int no_of_cmds = 0;

// 	mini->sp_pipes = malloc(100 * 100); 
// 	if (!mini->sp_pipes)
// 		return ;
// 	mini->sp_pipes = ft_split(mini->line, '|');
// 	while (mini->sp_pipes[no_of_cmds])
// 		no_of_cmds++;
// 	mini->no_cmds = no_of_cmds;
	
// }

// void prt_array(t_mini *mini)
// {
// 	int x = 0;
// 	int y = 0;
// 	int z = 0;
// 	if (!mini->sp_pipes || !mini->sp_quotes || !mini->sp_pipes[0] || !mini->sp_quotes[0])
// 		return ;

// 	while (mini->sp_quotes[y])
// 	{

// 		x = 0;
// 		ft_printf("\nsp_pipes%d = |%s|\n", y, mini->sp_pipes[y]);
// 		while (mini->sp_quotes[y][x])
// 		{
// 			ft_printf("sp_quotes%d<%s>",y, mini->sp_quotes[y][x]);
// 			// mini->sp_spaces[z++] = ft_split(mini->sp_quotes[y][x], ' ');
// 			x++;
// 		}
// 		y++;
// 	}
// 	ft_printf("\n");
// }

// void build_cmd(t_mini *mini)
// {
// 	int x = 0 ;
// 	int y = 0;
// 	while (mini->sp_pipes[x])
// 	{
// 		y =0;
// 		while (mini->sp_pipes[x][y] && mini->sp_pipes[x][y] != '/')
// 		{
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void print_array(t_mini *mini)
// {
// 	int x = 0;
// 	int y = 1;
// 	if (!mini->inputs || !mini->inputs[0])
// 		return ;
// 	while (mini->inputs[y])
// 	{
// 		x = 0;
// 		while (mini->inputs[y][x])
// 		{
// 			ft_printf("%d-%d - <%s>\n",y,x,mini->inputs[y][x]);
// 			x++;
// 		}
// 		ft_printf("\n");
// 		y++;
// 	}
// }

// void print_tkns(t_mini *mini)
// {
// 	while (mini->tokens != NULL)
// 	{
// 		ft_printf("sentence: %d, word: %d <%s>\ttype: %d\n",mini->tokens->sentence_no,mini->tokens->word_no, mini->tokens->word, mini->tokens->type);
// 		mini->tokens = mini->tokens->next;
// 	}
// }

// int	word_counter(const char *str, char c)
// {
// 	int	i;
// 	int	trigger;

// 	i = 0;
// 	trigger = 0;
// 	while (*str)
// 	{
// 		if (*str != c && trigger == 0)
// 		{
// 			trigger = 1;
// 			i++;
// 		}
// 		else if (*str == c)
// 			trigger = 0;
// 		str++;
// 	}
// 	return (i);
// }

// int main()
// {
// 	char input[42] = "asd patate/steak dsa/banane poire |das";
// 	t_mini mini;
// 	int i = 0;
// 	int index = 0;

// 	mini.inputs = NULL;
// 	mini.line = input;
// 	mini.tokens = NULL;
	
// 	ft_printf("input: %s\n\n", mini.line);
// 	if (!input[0])
// 		return (0);
// 	split_quotes(&mini);
// 	// index = split_sep(&mini);
// 	// if (mini.no_sentances != 1)
// 	split_spaces(&mini, index);
// 	ft_tokenize(&mini,1,0);
// 	print_array(&mini);
// 	print_tkns(&mini);

// 	ft_free_tpl_array(&mini);

// 	/*split the input into CMD|ARG|PIPE|ETC incuding QUOTES*/
// }