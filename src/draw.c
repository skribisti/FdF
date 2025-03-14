/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:59:13 by norabino          #+#    #+#             */
/*   Updated: 2025/03/14 09:51:40 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	if (!img->addr)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	draw_top(t_fdf *fdf)
{
	t_point	*current;

	if (!fdf->map)
		return (1);
	current = fdf->map->first;
	while (current)
	{
		my_mlx_pixel_put(fdf->img, current->x, current->y, current->color);
		current = current->next;
	}
	if (fdf->mlx && fdf->win && fdf->img->img)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return (0);
}

int	fdf_draw(t_fdf *fdf, int view)
{
	if (view == 0)
		draw_top(fdf);
	else if (view == 1)
		draw_iso(fdf);
	else if (view == 2)
		draw_parralel(fdf);
	fdf_link_points(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
}