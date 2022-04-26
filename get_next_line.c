/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbahraou <sbahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:40:20 by sbahraou          #+#    #+#             */
/*   Updated: 2022/04/26 09:37:16 by sbahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*splitline(char *ligne)
{
	int		i;
	char	*reste;

	i = 0;
	reste = 0;
	while (ligne[i] != '\0')
	{
		if (ligne[i] == '\n')
		{
			reste = substr(ligne, i + 1, ft_strlen(ligne) - i);
			if (reste[0] == '\0')
			{
				free(reste);
				return (0);
			}
			ligne[i + 1] = '\0';
			break ;
		}
		i++;
	}
	return (reste);
}

char	*createline(int fd, char *reste, char *str)
{
	int		ret;
	char	*ptr;

	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, str, BUFFER_SIZE);
		if (ret == 0)
			return (reste);
		else if (ret < 0)
			return (NULL);
		str[ret] = '\0';
		if (!reste)
			reste = ft_strdup("");
		ptr = reste;
		reste = ft_strjoin(reste, str);
		free(ptr);
		ptr = 0;
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (reste);
}

char	*get_next_line(int fd)
{
	char		*ligne;
	char		*str;
	static char	*reste;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	ligne = createline(fd, reste, str);
	free(str);
	str = 0;
	if (!ligne)
		return (NULL);
	reste = splitline(ligne);
	return (ligne);
}

int	main()
{
	int fd;

	fd = open("g.txt", O_RDONLY);
	
	// if (fd != -1)
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return 0;
}