/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamieta <anamieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:38:16 by anamieta          #+#    #+#             */
/*   Updated: 2023/11/30 15:07:42 by anamieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_concatenate(int *bytes_read, int fd, char *line)
// what is the line - it is an empty string that waits for the content of the buffer
// this function is focused on building the line as data is read, "/n" determines when to stop reading
// doesn't conatin "\n" at the end of the line
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
// its failing tests if I get rid of this line, but why do we need it if we used calloc?
// adding the null terminator explicitly can be seen as a defensive programming practice,
// ensuring that the buffer remains null-terminated regardless of changes in the code or potential variations
// in the memory allocation function used. It might be considered as a precautionary measure for code robustness.
		concatenated = ft_strjoin(line, buffer);
		free (line);
		// In practice, freeing the memory of the initial empty string before reassigning it with 
		// line = concatenated; is more of a defensive programming practice. It ensures that any memory 
		// previously allocated for line is properly released before assigning it a new value. This helps 
		// prevent memory leaks and ensures that the program does not consume more and more memory as it 
		// iterates through reading lines from the file.

		// Otherwise, you would lose reference to this memory block, and it would not be deallocated.
		// So, the free(line) before reassignment is crucial for preventing memory leaks. It ensures that 
		// the memory associated with the old content of line is properly released before assigning it to 
		// a new value. This is a good practice for memory management to avoid unnecessary memory consumption 
		// over multiple iterations.
		line = concatenated;
		if (ft_strchr(buffer, '\n')) // checking for first occurrence of the newline char in buffer
		// Placing the condition at the end of the loop ensures that the program checks for the presence of
		// a newline character only after reading a chunk of data into the buffer.
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

// read_and_concatenate actually created the line from a file, and its allocated and 
// properly terminated by get_result

char	*get_result(char *line, int bytes_read)
// bytes_read is the number of characters obtained by get_line_len
// The function allocates memory for the result based on the length of the line
// contains "\n" before "\0"
// it is used after read_and_concatenate has completed the process of building the line
// specifically handles creating a result string from the content of line, including the newline character 
// if it exists.
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
	// while it's not a newline character or null terminator
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
	// the purpose is to free it always because we dont need it
	new_line = ft_calloc((ft_strlen(line) - bytes_read + 1), sizeof(char));
	// after freeing the line, it is still used here up in strlen and below, why is it working?
	// at the bytes_read theres always a null terminator, so we're basically always freeing it
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

// void init_gnl(t_gnl *gnl, int argc, char **argv, char **env)
// {
// 	gnl->argc = argc;
// 	gnl->argv = argv;
// 	gnl->env = env;
// 	gnl->word = argv[1];
// }

// void parse_args(t_gnl *gnl)
// {

// }

// int main(int argc, char **argv, char **env)
// {
// 	t_gnl gnl;

// 	init_gnl(&gnl, argc, argv, env);
// 	parse_args(&gnl);
// }