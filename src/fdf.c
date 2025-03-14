/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/14 10:02:43 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#define WIDTH 1920
#define HEIGHT 1080

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
	fdf->img = malloc(sizeof(t_img));
	if (!fdf->img)
		return (1);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (free(fdf->img), 1);
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "FdF");
	if (!fdf->win)
		return (free(fdf->img), free(fdf->mlx), 1);
	fdf->img->img = mlx_new_image(fdf->mlx, 1920, 1080);
	if (!fdf->img->img)
		return (mlx_destroy_window(fdf->mlx, fdf->win), free(fdf->img), free(fdf->mlx), 1);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img, 
		&fdf->img->bits_per_pixel, &fdf->img->line_length, &fdf->img->endian);
	if (verif_all_ok(fdf))
		draw_points(fdf);
	mlx_hook(fdf->win, 17, 1L << 17, handle_close, &fdf);
	mlx_hook(fdf->win, 2, 1L << 0, handle_hook, &fdf);
	mlx_loop(fdf->mlx);
	return (1);
	return(0);
}
