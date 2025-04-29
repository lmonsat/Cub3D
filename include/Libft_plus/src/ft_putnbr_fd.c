/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 00:48:05 by lmonsat           #+#    #+#             */
/*   Updated: 2025/03/13 17:49:39 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long int	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}
/*#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int	main(void)
{
	int fd = open("test_ft_putnbr.txt",
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

	int nbr = 10;
	ft_putnbr_fd(nbr, fd);
	printf("number '%d' printed\n", nbr);

	close(fd);

	return (0);
}*/
