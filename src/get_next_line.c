/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:20:29 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/29 15:24:32 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*bank = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_bank(fd, &bank);
	if (bank == NULL)
		return (NULL);
	extract_line(bank, &line);
	reset_bank(&bank);
	if (line[0] == '\0')
	{
		free_bank(bank);
		bank = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_bank(int fd, t_list **bank)
{
	char	*buffer;
	int		size;

	size = 1;
	while (!find_newline(*bank) && size != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		size = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*bank == NULL && size == 0) || size == -1)
		{
			free(buffer);
			return ;
		}
		buffer[size] = '\0';
		add_in_bank(bank, buffer, size);
		free(buffer);
	}
}

void	add_in_bank(t_list **bank, char *buffer, int read)
{
	int		i;
	t_list	*last_in_bank;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc((read + 1) * sizeof(char));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < read)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*bank == NULL)
	{
		*bank = new_node;
		return ;
	}
	last_in_bank = get_last_node(*bank);
	last_in_bank->next = new_node;
}

int	find_newline(t_list *bank)
{
	int		i;
	t_list	*current_node;

	if (bank == NULL)
		return (0);
	current_node = get_last_node(bank);
	i = 0;
	while (current_node->content[i])
	{
		if (current_node->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*get_last_node(t_list *bank)
{
	t_list	*current_node;

	current_node = bank;
	while (current_node && current_node->next)
	{
		current_node = current_node->next;
	}
	return (current_node);
}

/*
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int	main(void)
{
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	if (fd == -1)
	{
		perror("Error");
		return (1);
	}

	char *string = "987654321098765432109876543210987654321098\n
	01234567890123456789012345678901234567890\n
	9876543210987654321098765432109876543210";
	ft_putstr_fd(string, fd);
	printf("string : '%s' printed\n\n", string);

	close(fd);

	fd = open("test.txt", O_RDONLY);

	if (fd == -1)
	{
		perror("Error");
		return (1);
	}

	char *result = get_next_line(fd);
	printf("next line '%s'\n", result);

		char *result2 = get_next_line(fd);
	printf("next line '%s'\n", result2);

		char *result3 = get_next_line(fd);
	printf("next line '%s'\n", result3);

		char *result4 = get_next_line(fd);
	printf("next line '%s'\n", result4);

		char *result5 = get_next_line(fd);
	printf("next line '%s'\n", result5);

		char *result6 = get_next_line(fd);
	printf("next line '%s'\n", result6);
	close(fd);


	return (0);
}*/