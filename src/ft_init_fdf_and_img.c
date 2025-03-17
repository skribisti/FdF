/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_fdf_and_img.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:05:31 by norabino          #+#    #+#             */
/*   Updated: 2025/03/17 15:50:28 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

t_fdf	*ft_init_img(t_fdf *fdf)
{
	fdf->img = malloc(sizeof(t_img));
	if (!fdf->img)
		return (NULL);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (free(fdf->img), NULL);
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "FdF");
	if (!fdf->win)
		return (free(fdf->img), free(fdf->mlx), NULL);
	fdf->img->img = mlx_new_image(fdf->mlx, 1920, 1080);
	if (!fdf->img->img)
		return (mlx_destroy_window(fdf->mlx, fdf->win), free(fdf->img), free(fdf->mlx), NULL);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img, 
		&fdf->img->bits_per_pixel, &fdf->img->line_length, &fdf->img->endian);
	return (fdf);
}

t_fdf	*ft_init_fdf(t_fdf *fdf)
{
	fdf->img = NULL;
	fdf->map = NULL;
	fdf->mlx = NULL;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->switch_view = 0;
	fdf->view = 0;
	fdf->win = NULL;
	fdf->zoom = 1.0;
	fdf = ft_init_img(fdf);
	return (fdf);
}

t_fdf	*ft_init_fdf_and_img()
{
	t_fdf	*fdf;
	fdf = (t_fdf *)malloc(sizeof(t_fdf));

	fdf = ft_init_fdf(fdf);
	return (fdf);
}