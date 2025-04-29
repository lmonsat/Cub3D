/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 06:01:11 by lmonsat           #+#    #+#             */
/*   Updated: 2024/03/25 22:57:10 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	free_bank(t_list *bank)
{
	t_list	*current_node;
	t_list	*next;

	current_node = bank;
	while (current_node)
	{
		free(current_node->content);
		next = current_node->next;
		free(current_node);
		current_node = next;
	}
}

void	extract_line(t_list *bank, char **line)
{
	int	i;
	int	j;

	if (bank == NULL)
		return ;
	generate_line(line, bank);
	if (line == NULL)
		return ;
	j = 0;
	while (bank)
	{
		i = 0;
		while (bank->content[i])
		{
			if (bank->content[i] == '\n')
			{
				(*line)[j++] = bank->content[i];
				break ;
			}
			(*line)[j++] = bank->content[i++];
		}
		bank = bank->next;
	}
	(*line)[j] = '\0';
}

void	reset_bank(t_list **bank)
{
	int		i;
	int		j;
	t_list	*last_in_bank;
	t_list	*node_reset;

	node_reset = malloc(sizeof(t_list));
	if (bank == NULL || node_reset == NULL)
		return ;
	node_reset->next = NULL;
	last_in_bank = get_last_node(*bank);
	i = 0;
	while (last_in_bank->content[i] && last_in_bank->content[i] != '\n')
		i++;
	if (last_in_bank->content && last_in_bank->content[i] == '\n')
		i++;
	node_reset->content = malloc(sizeof(char)
			* ((ft_strlen(last_in_bank->content) - i) + 1));
	if (node_reset->content == NULL)
		return ;
	j = 0;
	while (last_in_bank->content[i])
		node_reset->content[j++] = last_in_bank->content[i++];
	node_reset->content[j] = '\0';
	free_bank(*bank);
	*bank = node_reset;
}

<<<<<<< HEAD
void	generate_line(char **line, t_list *bank)
=======
char	*ft_strjoin(char *s1, char *s2)
{
	size_t			lenght;
	char			*join;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	lenght = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((lenght + 1) * (sizeof(char)));
	if (join == NULL)
		return (ft_free(join), NULL);
	while (ft_strlen(s1) > i)
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (ft_free(s1), join);
}

void	ft_free(char *ptr)
>>>>>>> origin/simple_solong
{
	int	i;
	int	len;

	len = 0;
	while (bank)
	{
		i = 0;
		while (bank->content[i])
		{
			if (bank->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		bank = bank->next;
	}
	*line = malloc((len + 1) * sizeof(char));
	if (*line == NULL)
		return ;
}
