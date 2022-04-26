/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 02:10:23 by sbahraou          #+#    #+#             */
/*   Updated: 2022/04/26 09:34:52 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nv;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (0);
	nv = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (nv)
	{
		i = 0;
		k = 0;
		while (s1[i])
		{
			nv[k++] = s1[i++];
		}
		i = 0;
		while (s2[i])
		{
			nv[k++] = s2[i++];
		}
		nv[k] = '\0';
		return (nv);
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*cp;
	int		i;

	i = 0;
	cp = (char *)malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (cp)
	{
		while (s1[i])
		{
			cp[i] = s1[i];
			i++;
		}
		cp[i] = '\0';
		return (cp);
	}
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	char			*s;

	s = (char *)str;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if (c == 0)
		return ((char *)s + i);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (ft_strdup(""));
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
