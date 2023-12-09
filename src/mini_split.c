/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:20:09 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/09 09:52:42 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	no_of_words(char *s, int trigger, int i, int no_wrds)
{
	while (s[i])
	{
		if (s[i] != ' ' && trigger == 0)
		{
			if (s[i] == 34)
				trigger = 2;
			else if (s[i] == 39)
				trigger = 3;
			else
				trigger = 1;
			no_wrds++;
		}
		else if (s[i] == ' ' && trigger == 1){
			trigger = 0;
		}
		if ((s[i] == '|' || s[i] == '/'))
		{
			if (trigger == 1)
				no_wrds++;
			trigger = 0;
		}
		if ((s[i] == 34 && trigger == 2) || (s[i] == 39 && trigger == 3))
			trigger = 0;
		i++;
	}
	return (no_wrds);
}

int	word_len(char *s, int start)
{
	int	trigger;
	int	len;

	trigger = 0;
	len = 0;
	if (s[start] == '|')
		return (1);
	while (s[start] || (len > 0 && trigger))
	{
		if (s[start] == ' ' && trigger == 0)
			return (len);
		else if (s[start] == 34 && trigger == 1)
			trigger = 0;
		else if (s[start] == 39 && trigger == 2)
			trigger = 0;
		else if ((s[start] == 39 && trigger == 0))
			trigger = 2;
		else if ((s[start] == 34) && trigger == 0)
			trigger = 1;
		else if (s[start] == '|' && trigger == 0)
			return (len);
		len++;
		start++;
	}
	return (len);
}

char	*substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s || !s[0] || len < 1 || start > (int)ft_strlen(s))
		return (NULL);
	if (len > (int)(ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i++] = s[start++];
	}
	str[i] = 0;
	return (str);
}

char	**mini_split(char *s)
{
	int		i;
	char	**split;
	int		no_wrds;
	int		len;
	int		wrd_no;

	i = 0;
	no_wrds = no_of_words(s, 0, 0, 0) + 1;
	split = malloc(sizeof(char *) * no_wrds + 2);
	if (!split)	
		return (NULL);
	wrd_no = -1;
	while (++wrd_no < no_wrds)
	{
		while (s[i] && s[i] == ' ')
			i++;
		len = word_len(s, i);
		split[wrd_no] = ft_substr(s, i, len);
		i += len;
	}
	split[wrd_no] = NULL;
	return (split);
}
