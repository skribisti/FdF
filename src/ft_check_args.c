/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:22:39 by norabino          #+#    #+#             */
/*   Updated: 2025/03/04 15:59:18 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] 
	&& i < ft_strlen(str1) && i < ft_strlen(str2))
		i++;
	return (str1[i] - str2[i]);
}

char *ft_take_extension(char **av)
{
	char *ext;
	int	i;

	i = 0;
	while (av[1][i] != '.' && av[1][i + 1])
		i++;
	if (i == ft_strlen(av[1]))
		return (NULL);
	ext = av[1] + (ft_strlen(av[1]) - 4);
	return (ext);
}

int	ft_check_open(char **av)
{
	char *file;
	int	fd;

	file = av[1];
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	return (1);
}

int	ft_check_args(int ac, char **av)
{
	char *extension;

	if (ac < 2)
		return(printf("Not enough arguments.\n"), 0);
	if (ac > 2)
		return(printf("Too much arguments.\n"), 0);
	extension = ft_take_extension(av);
	if (!extension)
		return(printf("No file extension.\n"), 0);
	if (ft_strcmp(extension, ".fdf" )!= 0)
		return(printf("Not good file extension.\n"), 0);
	if (!ft_check_open(av))
		return(printf("Error when opening file...\n"), 0);
	return (1);
}