/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:20 by sbahraou          #+#    #+#             */
/*   Updated: 2022/04/22 03:41:07 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

void split(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
}

char	*substr(char const *s, unsigned int start, size_t len)
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

void	function(char **reste, char **temp, int *i)
{
	// char	*temp;
	// int i;

	// i = 0;
	// j = &i;
	*i = 0;
	*temp = NULL;
	// printf("restee : %s\n", *reste);
	while (*(*reste + *i) != '\0')
	{
	// {printf("--%c-- i = %d--\n", *reste[i], i);
		if (*(*reste + *i) == '\n')
		{
			*temp = *reste;
			// i think free(reste);
			*reste = substr(*reste, *i + 1, ft_strlen(*reste + *i));
			*(*temp + *i + 1) = '\0';
			break ;
		}
		(*i)++;
		// printf("\nj : %d\n", *j);
	}
}

char *get_next_line(int fd)
{
	char		*temp = NULL;
	int			j;
	char		*str;
	static char *reste;
	int			ret;
	char		*nstr;

	str = malloc(BUFFER_SIZE + 1);
	j = 0;
	if (reste == NULL)
		reste = ft_strdup("");
	while ((ret = read(fd, str, BUFFER_SIZE)))
	{
		str[ret] = '\0';
		reste = ft_strjoin(reste, str);
		function(&reste, &temp, &j);
		if (temp != NULL)
			return (temp);
	}
	// printf("\nreste : %s",reste);
	free(str);
	function(&reste, &temp, &j);

	// printf("\nreste : %s\n", reste);
	if (temp != NULL)
			return (temp);
	if (j == ft_strlen(reste))
	{
		nstr = ft_strdup(reste);
		reste = NULL;
		return (nstr);
	}
	return (NULL);
}

int main()
{
	int fd;
	// OUVERTURE
	fd = open("test.txt", O_RDONLY);
	// fd = open("41_no_nl", O_RDWR);
	if (fd == -1)
	{
		printf("ERREUR d'ouverture de fichier");
		return (1);
	}
	// LECTURE
	// gnl(0, "01234567890123456789012345678901234567890\n")
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
//est ce que je doit ajouter un retour a ligne dans la derniere ligne?
	return (0);
}
