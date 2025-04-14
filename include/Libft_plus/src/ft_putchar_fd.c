/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:31:32 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 16:31:32 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int	main(void)
{
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	if (fd == -1) {
		perror("Error");
		return (1);
	}

	char character = 'A';
	ft_putchar_fd(character, fd);
	printf("character '%c' printed\n", character);

	close(fd);

	return (0);
}*/
