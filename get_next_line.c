/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchencha <nchencha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:31:25 by nchencha          #+#    #+#             */
/*   Updated: 2024/10/08 15:31:10 by nchencha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_newline(int fd, char *buffer)
{
	char	*buff;
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
	return (buffer);
}

char	*extract_line(char *buffer)
{
	char	*s;
	int		i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while ((buffer[i] != '\0') && buffer[i] != '\n')
		i++;
	s = malloc((i + 2) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
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
	int		c;
	char	*remain_str;

	i = 0;
	c = 0;
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
		return (0);
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = get_remainder(buffer);
	return (line);
}
