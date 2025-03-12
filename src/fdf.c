/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/12 10:34:55 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#define WIDTH 1920
#define HEIGHT 1080

int fdf_func(t_fdf *fdf)
{
	init_window_img(fdf);
	//draw_points(fdf, &vars, &img);
	//link_points();
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;
	t_map	*map;
	
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	map = (t_map *)malloc(sizeof(t_map *));
	if (!fdf || !map)
		return (1);
	fdf->map = map;
	if (!ft_check_args(ac, av))
		return (1);
	ft_init_map(fdf, av);
	fdf_func(fdf);
	return(0);
}
