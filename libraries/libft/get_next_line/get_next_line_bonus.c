/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:11:21 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 15:04:06 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(char *temp)
{
	size_t	i;

	if (!temp || !*temp)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	return (ft_substr_gnl(temp, 0, i));
}

static char	*update_temp(char *temp, char *buffer)
{
	char	*old_temp;

	if (!temp)
		temp = ft_strdup_gnl(buffer);
	else
	{
		old_temp = temp;
		temp = ft_strjoin_gnl(temp, buffer);
		free(old_temp);
	}
	return (temp);
}

static char	*get_temp(int fd, char *temp)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_gnl(temp, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = update_temp(temp, buffer);
		if (!temp)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (temp);
}

static char	*atua_temp(char *temp)
{
	size_t	i;
	char	*new_temp;

	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	new_temp = ft_substr_gnl(temp, i, ft_strlen_gnl(temp) - i);
	free(temp);
	return (new_temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*temp[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp[fd] = get_temp(fd, temp[fd]);
	if (!temp[fd])
		return (NULL);
	line = get_line(temp[fd]);
	if (!line)
	{
		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	temp[fd] = atua_temp(temp[fd]);
	return (line);
}

/*int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (argc != 3)
	{
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		return (1);
	}
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		printf("open failed");
		return (1);
	}
	printf("Reading from both files...\n");
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line1 && !line2)
			break ;
		if (line1)
		{
			printf("File 1, Line %d: %s", ++i, line1);
			free(line1);
		}
		if (line2)
		{
			printf("File 2, Line %d: %s", ++j, line2);
			free(line2);
		}
	}
	printf("Finished reading both files.\n");
	close(fd1);
	close(fd2);
	return (0);
}*/
