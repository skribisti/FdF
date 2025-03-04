/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:38:08 by norabino          #+#    #+#             */
/*   Updated: 2025/03/04 15:58:56 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_read_to_remainder(int fd, char *remainder)
{
	char	*buffer;
	int		read_bytes;

	if (remainder && ft_strchr(remainder, '\n'))
		return (remainder);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(remainder, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(remainder), remainder = 	NULL, free(buffer), NULL);
		if (read_bytes == 0 && !remainder)
			return (free(buffer), NULL);
		buffer[read_bytes] = 0;
		remainder = ft_strjoin(remainder, buffer);
		if (!remainder)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainder);
}

char	*ft_get_a_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	if (!remainder[0] || !remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = ft_substr(remainder, 0, i + 1);
	if (!line && remainder)
	{
		free(remainder);
		return (NULL);
	}
	return (line);
}

char	*ft_new_remainder(char *remainder)
{
	int		i;
	char	*new;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
		return (free(remainder), remainder = NULL, NULL);
	i++;
	new = ft_substr(remainder, i, ft_strlen(remainder) - i);
	if (!new)
		return (NULL);
	if (remainder)
	{
		free(remainder);
		remainder = NULL;
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char		*remainder;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_read_to_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = ft_get_a_line(remainder);
	remainder = ft_new_remainder(remainder);
	return (line);
}
