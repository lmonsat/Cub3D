/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 05:50:16 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/29 15:15:57 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
int					find_newline(t_list *bank);
t_list				*get_last_node(t_list *bank);
void				read_and_bank(int fd, t_list **bank);
void				add_in_bank(t_list **bank, char *buffer, int read);
void				extract_line(t_list *bank, char **line);
void				generate_line(char **line, t_list *stash);
void				reset_bank(t_list **bank);
size_t				ft_strlen(const char *s);
void				free_bank(t_list *bank);

#endif
