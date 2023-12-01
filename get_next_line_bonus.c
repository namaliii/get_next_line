/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:56:30 by anamieta          #+#    #+#             */
/*   Updated: 2023/12/01 12:51:50 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_concatenate(int *bytes_read, int fd, char *line)
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
		buffer[*bytes_read] = '\0';
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
	static char	*line[OPEN_MAX];
	char		*result;
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	line[fd] = read_and_concatenate(&bytes_read, fd, line[fd]);
	if (!line[fd])
		return (NULL);
	bytes_read = get_line_len(line[fd]);
	result = get_result(line[fd], bytes_read);
	line[fd] = allocate_new_line(line[fd], bytes_read);
	return (result);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main() {
//     int file1 = open("s.txt", 'r');
// 	printf("fd for file1: %d\n", file1);
// 	int file2 = open("c.txt", 'r');
// 	printf("fd for file2: %d\n\n", file2);
//     if (file1 < 0) {
//         printf("Failed to open the file1.\n");
//         return 1;
//     }
// 	if (file2 < 0) {
//         printf("Failed to open the file2.\n");
//         return 1;
//     }
//     char* line1;
// 	char* line2;
//     // Read the first line
//     line1 = get_next_line(file1);
//     line2 = get_next_line(file2);
//     if (line1) {
//         printf("first line1: %s", line1);
//     }
// 	    while (line1)
// 	{
// 		line1 = get_next_line(file1);
// 		if (line1)
// 		{
// 			printf("next line1: %s", line1);
// 		}
// 	}
// 	printf("\n");
// 	if (line2) {
//         printf("first line2: %s", line2);
//     }
// 	while (line2)
// 	{
// 	line2 = get_next_line(file2);
// 		if (line2)
// 		{
// 			printf("next line2: %s", line2);
// 		}
// 	}
//     // Clean up
//     close(file1);
// 	close(file2);
//     return 0;
// }
