/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 02:10:23 by sbahraou          #+#    #+#             */
/*   Updated: 2022/04/16 01:54:07 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (0);
	if (len < (ft_strlen(s) - start))
	{
		while (len > 0)
		{
			sub[i++] = s[start++];
			len--;
		}
		sub[i] = '\0';
	}
	else
		sub = ft_memcpy(sub, s + start, len);
	return (sub);
}

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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
