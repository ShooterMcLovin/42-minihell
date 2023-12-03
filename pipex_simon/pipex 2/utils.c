/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:01:34 by siroulea          #+#    #+#             */
/*   Updated: 2023/09/30 15:17:22 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_isin(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	int		i;
	int		i2;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && ft_isin(s1[i], set))
		i++;
	start = i;
	end = ft_strlen((char *)s1) - 1;
	while (end >= start && ft_isin(s1[end], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	i = start;
	i2 = 0;
	while (i <= end)
		str[i2++] = s1[i++];
	str[i2] = '\0';
	return (str);
}

static char	*ft_substr2(size_t i, size_t len, unsigned int start, char const *s)
{
	size_t	i2;
	char	*str;

	i2 = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && i2 < len)
		{
			str[i2] = s[i];
			i2++;
		}
		i++;
	}
	str[i2] = 0;
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (size_t)ft_strlen(s))
	{
		len = 0;
		start = 0;
	}
	if (len > (size_t)ft_strlen((char *)&s[start]))
		len = (size_t)ft_strlen((char *)&s[start]);
	if (!s)
		return (NULL);
	str = ft_substr2(i, len, start, s);
	return (str);
}
