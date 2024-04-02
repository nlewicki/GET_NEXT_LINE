/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:10 by nlewicki          #+#    #+#             */
/*   Updated: 2024/04/02 14:54:23 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *save)
{
	int		read_bytes;
	char	*buffer;
	char	*tmp;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		buffer[read_bytes] = '\0';
		if (save == NULL)
			save = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(save, buffer);
			free(save);
			save = tmp;
		}
		if (ft_strchr(save, '\n'))
			break ;
		read_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (read_bytes < 0)
	{
		free(save);
		save = NULL;
	}
	return (save);
}


char	*get_next_line(int fd)
{
	int			i;
	char		*line;
	static char	*save;
	char		*tmp;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read(fd, save);
	if (save == NULL || (save[0] == '\0' && ft_strlen(save) == 0))
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\n')
	{
		line = ft_substr(save, 0, i + 1);
		printf("line: %s", line);
		tmp = save;
		save = ft_substr(save, i + 1, ft_strlen(save) - i);
		if (save == NULL)
			printf("save: NULL\n\n");
		else
			printf("save: %s\n\n", save);
		free(tmp);
	}
	else
	{
		line = ft_strdup(save);
		free(save);
		save = NULL;
	}
	return (line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return (1);
	}
	while (i < 8)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
