/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:59:13 by norabino          #+#    #+#             */
/*   Updated: 2025/03/12 10:47:10 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	draw_points(t_fdf *fdf)
{
	t_point	*current;

	current = fdf->map->first;
	while (current)
	{
		if (current->z == 0 && fdf->img)
			my_mlx_pixel_put(fdf->img, current->x, current->y, create_trgb(0, 255, 0, 0));
		current = current->next;
	}
	if (fdf->mlx && fdf->win && fdf->img->img)
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return (0);
}