/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchencha <nchencha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:31:25 by nchencha          #+#    #+#             */
/*   Updated: 2024/10/10 11:46:57 by nchencha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_newline(int fd, char *buffer)
{
	char 	*buff;
	int		read_bytes;
	
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
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
	free(buff);
	return(buffer);
}

char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
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
	int 	c;
	char	*remain_str;

	i = 0;
	c = 0;
	// Find the first newline character or the end of the string
	while ((buffer[i] != '\0') && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	remain_str = malloc((gnl_strlen(buffer) - i + 1) * sizeof(char));
	if (!remain_str)
		return (NULL);
	i++;
	while (buffer[i])
		remain_str[c++] = buffer[i++];
	remain_str[c] = '\0';
	
	free(buffer);
	return (remain_str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = get_remainder(buffer);
	return (line);
}
