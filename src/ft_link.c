/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:15:49 by norabino          #+#    #+#             */
/*   Updated: 2025/03/24 11:11:23 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	create_gradient(t_point *p1, t_point *p2, t_bresenham *bres)
{
	float	total_dist;
	float	current_dist;
	float	percent;
	int		rgb[3];

	if (p1->color == p2->color)
		return (p1->color);
	total_dist = sqrt(pow(p2->draw_x - p1->draw_x, 2)
			+ pow(p2->draw_y - p1->draw_y, 2));
	if (total_dist == 0)
		return (p1->color);
	current_dist = sqrt(pow(bres->x - p1->draw_x, 2)
			+ pow(bres->y - p1->draw_y, 2));
	percent = current_dist / total_dist;
	if (percent > 1)
		percent = 1;
	if (percent < 0)
		percent = 0;
	ft_calc_colors(p1, p2, rgb, percent);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	ft_link(t_fdf *fdf, t_bresenham *bres, t_point *p1, t_point *p2)
{
	int	gradient;

	init_bresenham(bres, p1, p2);
	while (1)
	{
		if (fdf_coords_in_window((float)bres->x, (float)bres->y))
		{
			gradient = create_gradient(p1, p2, bres);
			if (gradient != 0)
				my_mlx_pixel_put(fdf->img, bres->x, bres->y, gradient);
		}
		if (bres->x == (int)p2->draw_x && bres->y == (int)p2->draw_y)
			break ;
		bres->e2 = bres->delta * 2;
		if (bres->e2 >= -bres->delta_y)
		{
			bres->delta -= bres->delta_y;
			bres->x += bres->slope_x;
		}
		if (bres->e2 < bres->delta_x)
		{
			bres->delta += bres->delta_x;
			bres->y += bres->slope_y;
		}
	}
}

int	fdf_link_points(t_fdf *fdf)
{
	t_point		*point;
	t_bresenham	*bres;

	point = fdf->map->first;
	bres = malloc(sizeof(t_bresenham));
	if (!bres)
		return (1);
	while (point)
	{
		if (point->right_point)
			ft_link(fdf, bres, point, point->right_point);
		if (point->bottom_point)
			ft_link(fdf, bres, point, point->bottom_point);
		point = point->next;
	}
	free(bres);
	return (0);
}
