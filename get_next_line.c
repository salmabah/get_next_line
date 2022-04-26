/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:20 by sbahraou          #+#    #+#             */
/*   Updated: 2022/04/26 03:15:04 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


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

void	splitline(char **reste, char **temp, size_t *i)
{
	char *temp1 = *temp;
	char *reste1 = *reste;
	int i1 = *i;

	i1 = 0;
	temp1 = NULL;
	while (reste1[i1] != '\0')
	{
		if (reste1[i1] == '\n')
		{
			temp1 = reste1;
			// i think free(reste);
			
			reste1 = substr(reste1, i1 + 1, ft_strlen(reste1) -i1 + 1);
			if(reste1[0] == 0)
			{
				free(reste1);
				reste1 = 0;
			}
			temp1[i1 + 1] = '\0';
			break ;
		}
		i1++;
	}
	 *i = i1;
	 *reste = reste1;
	 *temp = temp1;
	
}

char *createbuffer(int fd, char *reste, char *str, char *ligne)
{
	int		ret;
	char	*ptr;
	size_t	j;

	ret = 1;
	j = 0;
	if (reste == NULL)
		reste = ft_strdup("");
	while (ret)
	{
		ret = read(fd, str, BUFFER_SIZE);
		if (ret == 0)
			return (reste);
		else if (ret == -1)
			return (NULL);
		str[ret] = '\0';
		ptr = reste;
		reste = ft_strjoin(reste, str);
		free(ptr);
		ptr = 0;
		splitline(&reste, &ligne, &j);
		if (ligne != NULL)
			break;
			// return (temp);
	}
	return (reste);
}

char *get_next_line(int fd)
{
	char		*ligne;
	size_t			j;
	char		*str;
	static char *reste;
	char		*ptr;

	ligne = 0;
	if (fd < -1 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);

	reste = createbuffer(fd, reste, str, ligne);	
	free(str);
	str = 0;
	if (ligne != NULL)
		return (ligne);
	splitline(&reste, &ligne, &j);
	if (ligne != NULL)
		return (ligne);

	if (j == ft_strlen(reste))
	{
		ptr = reste;
		reste = NULL;
		if(ft_strlen(ptr) == 0)
		{
			free(ptr);
			ptr = 0;
		}
		return (ptr);
	}
	return (reste);
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
	// fd = 0;
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	
	
//est ce que je doit ajouter un retour a ligne dans la derniere ligne?
	return (0);
}
