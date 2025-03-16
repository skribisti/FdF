/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:05:31 by norabino          #+#    #+#             */
/*   Updated: 2025/03/16 14:22:42 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

int	ft_init_img(t_fdf *fdf)
{
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
	return (0);
}