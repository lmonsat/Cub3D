/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 00:46:29 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 17:49:32 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	endl;

	endl = '\n';
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, &endl, 1);
}
/*#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int	main(void)
{
	int fd = open("test_ft_putendl.txt",
	O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	//  O_WRONLY : Constante indiquant à la fonction open()
	que le fichier doit être ouvert en mode écriture seulement

	//  O_CREAT : Constante indiquant à la fonction open()
	de créer le fichier s'il n'existe pas déjà

	//  O_TRUNC : Constante indiquant à la fonction open()
	de tronquer le fichier à une longueur de zéro dès son ouverture

	//  S_IRUSR : Constante représentant les permissions
	de lecture pour le propriétaire du fichier

	//  S_IWUSR : Constante représentant les permissions
	d'écriture pour le propriétaire du fichier

	if (fd == -1)
	{
		perror("Error");
		return (1);
	}

	char *string = "Hello, World!";
	ft_putendl_fd(string, fd);
	printf("string '%s' printed\n", string);

	close(fd);

	return (0);
}*/
