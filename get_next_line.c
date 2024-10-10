/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchencha <nchencha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:31:25 by nchencha          #+#    #+#             */
/*   Updated: 2024/10/10 11:57:04 by nchencha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_newline(int fd, char *buffer)
{
	char	*tmp_buff;
	int		read_bytes;

	tmp_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_buff)
		return (NULL);
	read_bytes = 1;
	while (gnl_strchr(buffer, '\n') == NULL && read_bytes != 0)
	{
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
	return (buffer);
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
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
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

char	*get_remainder(char *buffer)
{
	int		i;
	int		j;
	char	*remain_str;

	i = 0;
	j = 0;
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
		remain_str[j++] = buffer[i++];
	remain_str[j] = '\0';
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
