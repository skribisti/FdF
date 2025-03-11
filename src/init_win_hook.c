/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:12:53 by norabino          #+#    #+#             */
/*   Updated: 2025/03/11 15:23:19 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_close(t_vars *vars)
{
	printf("Window closed using the red cross button.\n");
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}

int	init_window_img(t_fdf *fdf, t_vars *vars, t_img *img)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "FdF");
	img->img = mlx_new_image(vars->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	draw_points(fdf, vars, img);
	mlx_hook(vars->win, 17, 0, handle_close, &vars);
	mlx_loop(vars->mlx);
	return (1);
}