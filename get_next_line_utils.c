/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchencha <nchencha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:29:38 by nchencha          #+#    #+#             */
/*   Updated: 2024/10/09 21:12:13 by nchencha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*gnl_strchr(char *str, int ch)
{
	unsigned int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (ch == '\0')
		return ((char *)&str[gnl_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char) ch)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = -1;
	j = 0;
	if (!str1)
	{
		str1 = (char *)malloc(1 * sizeof(char));
		str1[0] = '\0';
	}
	if (!str1 || !str2)
		return (NULL);
	res = malloc(((gnl_strlen(str1) + gnl_strlen(str2)) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (str1 != NULL)
		while (str1[++i] != '\0')
			res[i] = str1[i];
	while (str2[j] != '\0')
		res[i++] = str2[j++];
	res[gnl_strlen(str1) + gnl_strlen(str2)] = '\0';
	if (str1[0] == '\0' && gnl_strlen(str1) == 0)
		free(str1);
	return (res);
}

/*
int main()
{
	// int count = gnl_strlen(NULL);
	// printf("%d", count);

	// char *result = gnl_strchr("Hello, Hi", '\0');
	// printf("%s", result);

	// char *result = gnl_strjoin("Hello", " World!");
	// printf("%s", result);
	// free(result);
}
*/