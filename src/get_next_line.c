/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:40:34 by drenquin          #+#    #+#             */
/*   Updated: 2024/05/21 14:31:38 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	cut_buffer(char *buffer)
{
	size_t	i;

	i = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (i);
}

size_t	check_buffer(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
			return (0);
		else
			i++;
	}
	return (1);
}

char	*get_line(int fd)
{
	char	*line;
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer || bytes_read == -1)
		return (ft_free(buffer), NULL);
	buffer[bytes_read] = '\0';
	line = NULL;
	while (check_buffer(buffer) == 1)
	{
		line = ft_strjoin(line, buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(buffer), ft_free(line), NULL);
		buffer[bytes_read] = '\0';
	}
	if (check_buffer(buffer) == 0)
		line = ft_strjoin(line, buffer);
	return (ft_free(buffer), line);
}

char	*get_next_line(int fd)
{
	char		*line_tip;
	char		*line;
	static char	*tip;
	char		*result;

	if (cut_buffer(tip) == ft_strlen(tip))
		line_tip = get_line(fd);
	else
		line_tip = ft_strdup(tip);
	line = ft_substr(line_tip, 0, cut_buffer(line_tip));
	if (cut_buffer(tip) == ft_strlen(tip))
		result = ft_strjoin(tip, line);
	else
	{
		result = ft_strdup(line);
		ft_free(tip);
	}
	ft_free(line);
	tip = NULL;
	if (ft_strlen(line_tip) - cut_buffer(line_tip) > 0)
		tip = ft_substr(line_tip, cut_buffer(line_tip), ft_strlen(line_tip));
	ft_free (line_tip);
	return (result);
}
