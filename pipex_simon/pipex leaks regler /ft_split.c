/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:07:04 by siroulea          #+#    #+#             */
/*   Updated: 2023/10/11 15:28:37 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	return (i);
}

static int	count_words(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**words;
	int		i;
	int		i2;
	int		len;

	i = 0;
	i2 = -1;
	if (!s)
		return (NULL);
	words = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (NULL);
	while (++i2 < count_words(s, c))
	{
		while (s[i] == c)
			i++;
		len = word_len(&s[i], c);
		if (s[i])
			words[i2] = ft_substr(&s[i], 0, len);
		if (words[i2] == NULL)
			return (ft_free(*words));
		i += len;
	}
	words[i2] = 0;
	return (words);
}

void	error(void)
{
	close_fd();
	free_all();
	perror("Error");
	exit(EXIT_FAILURE);
}
