/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpicard <alpicard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:41:25 by alpicard          #+#    #+#             */
/*   Updated: 2023/12/03 10:09:51 by alpicard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	*ft_release(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return (NULL);
}

static int	word_counter(const char *str, char *c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (!ft_strchr(c, *str) && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (ft_strchr(c, *str) != 0)
			trigger = 0;
		str++;
	}
	return (i);
}

static size_t	ft_word_len(char const *s, char *c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (0);
	while (s[i] != c[0] && s[i] != c[1] && s[i] != c[2] && s[i])
		i++;
	return (i);
}

char	**ft_split2(char const *s, char *c)
{
	char	**split;
	int		wrd_num;
	int		i;
	size_t	len;


	if (!s || !c)
		return (NULL);

	split = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!split)
		return (NULL);w
	i = 0;
	wrd_num = -1;
	len = 0;
	while (++wrd_num < word_counter(s, c))
	{
		while (ft_strchr(c, s[i]) != 0 && s[i])
			i++;
		len = ft_word_len(&s[i], c);
		split[wrd_num] = ft_substr(&s[i], 0, len);
		ft_printf("-%s-\n", split[wrd_num]);
		if (split[wrd_num] == NULL)
			return (ft_release(split));
		i += len;
	}
	split[wrd_num] = NULL;
	return (split);
}

// int main()
// {
// 	int x = 0;
// 	char ** split = ft_split2("ls|ls", "<>|");
// 	while (split[x])
// 	{
// 		ft_printf("%s\n", split[x]);
// 		x++;
// 	}
// }
