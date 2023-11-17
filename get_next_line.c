/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:38:16 by anamieta          #+#    #+#             */
/*   Updated: 2023/11/17 19:29:51 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_concatenate(int *bytes_read, int fd, char *line) // what is the line
{
	char	*buffer;
	char	*concatenated;

	if (!line)
		line = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (*bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (free(buffer), NULL);
		buffer[*bytes_read] = '\0'; // its failing tests if I get rid of this line, but why do we need it if we used calloc?
		concatenated = ft_strjoin(line, buffer);
		free (line);
		line = concatenated;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (line);
}

int	get_line_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	return (i);
}

char	*get_result(char *line, int bytes_read)
{
	char	*result;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	result = ft_calloc(bytes_read + 2, sizeof(char));
	if (!result)
		return (NULL);
	while (line[i] != '\n' && line[i])
	{
		result[i] = line[i];
		i++;
	}
	if (line[i] == '\n' && line[i])
		result[i] = '\n';
	return (result);
}

char	*allocate_new_line(char *line, int bytes_read)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!line[bytes_read])
	{
		free(line);
		return (NULL);
	}
	new_line = ft_calloc((ft_strlen(line) - bytes_read + 1), sizeof(char));
	if (!new_line)
		return (NULL);
	bytes_read++;
	while (line[bytes_read])
	{
		new_line[i] = line[bytes_read];
		i++;
		bytes_read++;
	}
	free (line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*result;
	int			bytes_read;
	int			i;

	i = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	line = read_and_concatenate(&i, fd, line);
	if (!line)
		return (NULL);
	bytes_read = get_line_len(line);
	result = get_result(line, bytes_read);
	line = allocate_new_line(line, bytes_read);
	return (result);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main() {
//     int file = open("s.txt", 'r');
//     if (file < 0) {
//         printf("Failed to open the file.\n");
//         return 1;
//     }
//     char* line;
//     // Read the first line
//     line = get_next_line(file);
//     if (line) {
//         printf("first line: %s\n", line);
//     }
//     while (line)
// 	{
// 		line = get_next_line(file);
// 		if (line)
// 		{
// 			printf("next line: %s\n", line);
// 		}
// 	}
//     // Clean up
//     close(file);
//     return 0;
// }
