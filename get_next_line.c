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
	char 	*tmp_buff;
	int		read_bytes;
	
	tmp_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buff)
		return (NULL);
	read_bytes = 1;
	//Find new line
	while (gnl_strchr(buffer, '\n') == NULL && read_bytes != 0)
	{
		//The read function reads up to BUFFER_SIZE bytes from the file descriptor fd and stores them in tmp_buff
		/*
			read()
			Positive value -> read somedata
			0 -> EOF
			-1 -> error
		*/
		read_bytes = read(fd, tmp_buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(tmp_buff);
			return (NULL);
		}
		tmp_buff[read_bytes] = '\0';
		buffer = gnl_strjoin(buffer, tmp_buff);
	}
	free(tmp_buff);
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
	char	*line;
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
	line = malloc((i + 2) * sizeof(char));
	//Check if memory allocation fail
	if (!line)
		return (NULL);
	i = 0;
	//Copy Character from buffer to line
	while ((buffer[i] != '\0') && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*
	Goal: Extract and return the remainder of the buffer after the first newline character (\n). If there is no newline character in the buffer, the function returns NULL and frees the buffer.
	Use Case: In a line-reading function like get_next_line, after extracting the first line, this function is used to save the remaining content in the buffer for subsequent reads.
*/

char	*get_remainder(char *buffer)
{
	int		i;
	int 	j;
	char	*remain_str;

	i = 0;
	j = 0;
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
		remain_str[j++] = buffer[i++];
	remain_str[j] = '\0';
	
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