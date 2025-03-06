/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/06 09:43:40 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*int fdf(int ac, char **av)
{
	ac = 0;
	av[0][0] = 0;
	printf("allo");
	return (0);
}*/

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;

	if (!ft_check_args(ac, av))
		return (1);
	ft_init_map(av);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	//fdf(ac, av);
	return(0);
}
