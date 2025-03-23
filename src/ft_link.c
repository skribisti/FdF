/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:15:49 by norabino          #+#    #+#             */
/*   Updated: 2025/03/23 14:49:02 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_bresenham(t_bresenham *bres, t_point *p1, t_point *p2)
{
	bres->delta_x = abs((int)p2->draw_x - (int)p1->draw_x);
	bres->delta_y = abs((int)p2->draw_y - (int)p1->draw_y);
	bres->delta = bres->delta_x - bres->delta_y;
	bres->x = (int)p1->draw_x;
	bres->y = (int)p1->draw_y;
	if (p1->draw_x < p2->draw_x)
		bres->slope_x = 1;
	else
		bres->slope_x = -1;
	if (p1->draw_y < p2->draw_y)
		bres->slope_y = 1;
	else
		bres->slope_y = -1;
}

void	check_colors(int *red, int *green, int *blue)
{
	int *colors[3];
	int	i;

	colors[0] = red;
	colors[1] = green;
	colors[2] = blue;
	i = 0;
	while (colors[i])
	{
		if (*colors[i] < 0)
			*colors[i] = 0;
		if (*colors[i] > 255)
			*colors[i] = 255;
		i++;
	}
}

int	create_gradient(t_point *p1, t_point *p2, t_bresenham *bres)
{
	float total_dist;
	float current_dist;
	float	percent;
	int		red;
	int		green;
	int		blue;

	if (p1->color == p2->color)
		return (p1->color);
	total_dist = sqrt(pow(p2->draw_x - p1->draw_x, 2) + pow(p2->draw_y - p1->draw_y, 2));
	if (total_dist == 0)
		return (p1->color);
	current_dist = sqrt(pow(bres->x - p1->draw_x, 2) + pow(bres->y - p1->draw_y, 2));
	percent = current_dist / total_dist;
	if (percent > 1)
		percent = 1;
	if (percent < 0)
		percent = 0;
	red = (int)((p1->color >> 16) + percent * ((p2->color >> 16)
				- (p1->color >> 16)));
	green = (int)((p1->color >> 8 & 0xFF) + percent * ((p2->color >> 8 & 0xFF)
				- (p1->color >> 8 & 0xFF)));
	blue = (int)((p1->color & 0xFF) + percent * ((p2->color & 0xFF)
				- (p1->color & 0xFF)));
	check_colors(&red, &green, &blue);
	return ((red << 16) | (green << 8) | blue);
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
		//my_mlx_pixel_put(fdf->img, bres->x, bres->y, create_trgb(1, 255, 255, 255));
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