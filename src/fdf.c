/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/04 10:54:51 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int fdf(int ac, char **av)
{
	ac = 0;
	av[0][0] = 0;
	printf("allo");
	return (0);
}

int	main(int ac, char **av)
{
	if (!ft_check_args(ac, av))
		return (1);
	ft_init_map(av);
	fdf(ac, av);
	return(0);
}