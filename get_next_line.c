/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchencha <nchencha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:31:25 by nchencha          #+#    #+#             */
/*   Updated: 2024/10/08 14:48:34y nchencha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
read_until_newline function reads chunks of data from the file descriptor 
until it finds a newline character or reaches the end of the file.
*/

char	*read_until_newline(int fd, char *buffer)
{
	char 	*buff;
	int		read_bytes;
	
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!gnl_strchr(buffer, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		buffer = gnl_strjoin(buffer, buff);
	}
	free(buff);
	return(buffer);
}

/*
 extract and return a line of text from the given string buffer. 
 It looks for a newline character (\n) or the end of the string, 
 allocates enough memory for the line (including the newline, if present), 
 and returns a newly allocated string containing the line
*/

char	*extract_line(char *buffer)
{
	char	*s;
	int		i;
	
	i = 0;
	//Check if the string if empthy
	if (buffer[i] == '\0')
		return (NULL);
	//Find the end of line or new line character
	while ((buffer[i] != '\0') && buffer[i] != '\n')
		i++;
	//Allocate memory for new line
	// + 2 -> newline character (if it is exitsts) , another one is for null terminator
	s = malloc((i + 2) * sizeof(char));
	//Check if memory allocation fail
	if (!s)
		return (NULL);
	i = 0;
	//Copy Character from buffer to s
	while ((buffer[i] != '\0') && buffer[i] != '\n')
	{
		s[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		s[i] = buffer[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*get_remainder(char *buffer)
{
	int		i;
	int 	c;
	char	*remain_str;

	i = 0;
	c = 0;
	// Find the first newline character or the end of the string
	while ((buffer[i] != '\0') && buffer[i] != '\n')
		i++;
	// if buffer is empthy string free buffer
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	remain_str = malloc((gnl_strlen(buffer) - i + 1) * sizeof(char));
	if (!remain_str)
		return (NULL);
	//Skip new line character
	i++;
	while (buffer[i])
		remain_str[c++] = buffer[i++];
	remain_str[c] = '\0';
	
	free(buffer);
	return (remain_str);
}

/*
The function reads data from the file descriptor (fd) and returns the next line
Including the newline character (\n), if it exists. 
It keeps the remaining data in the buffer for the next call.
*/
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	/*
	Call 'extract_line' to extract the first line from 'buffer' 
	(up to and including the newline character).
	*/
	line = extract_line(buffer);
	/*
	Call 'get_remainder' to update 'buffer' to 
	contain everything after the extracted line.
	*/
	buffer = get_remainder(buffer);
	return (line);
}