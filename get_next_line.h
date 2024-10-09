/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchencha <nchencha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:06:18 by nchencha          #+#    #+#             */
/*   Updated: 2024/10/09 19:27:22 by nchencha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

size_t	gnl_strlen(char *str);

char	*gnl_strchr(char *str, int ch);
char	*gnl_strjoin(char *str1, char *str2);

char	*get_next_line(int fd);
char	*read_until_newline(int fd, char *buffer);
char	*extract_line(char *buffer);
char	*get_remainder(char *buffer);

#endif