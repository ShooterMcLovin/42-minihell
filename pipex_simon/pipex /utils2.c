/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:37:50 by siroulea          #+#    #+#             */
/*   Updated: 2023/10/09 13:58:29 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_free(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

void	ft_free_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		i2;

	i = -1;
	i2 = -1;
	if (s1 == NULL)
	{
		s1 = ft_calloc(sizeof(char), 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = 0;
	}
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++i2])
		dest[i + i2] = s2[i2];
	dest[i + i2] = '\0';
	return (s1 = ft_free(s1), dest);
}

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	i2;

	{
		if (needle[0] == '\0')
			return ((char *)haystack);
		i2 = 0;
		while (i2 < len && haystack[i2])
		{
			i = 0;
			while (i2 < len && needle[i] && haystack[i2]
				&& needle[i] == haystack[i2])
			{
				++i;
				++i2;
			}
			if (needle[i] == '\0')
				return ((char *)&haystack[i2 - i]);
			i2 = i2 - i + 1;
		}
		return (0);
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(count * size);
	if (dest == NULL)
		return (NULL);
	while (i < (count * size))
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
