/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:15:49 by norabino          #+#    #+#             */
/*   Updated: 2025/03/19 14:57:42 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_bresenham(t_bresenham *bres, t_point *p1, t_point *p2)
{
	bres->delta_x = abs(p2->draw_x - p1->draw_x);
	bres->delta_y = abs(p2->draw_y - p1->draw_y);
	bres->delta = bres->delta_x - bres->delta_y;
	bres->x = p1->draw_x;
	bres->y = p1->draw_y;
	if (p1->draw_x < p2->draw_x)
		bres->slope_x = 1;
	else
		bres->slope_x = -1;
	if (p1->draw_y < p2->draw_y)
		bres->slope_y = 1;
	else
		bres->slope_y = -1;
}

int	create_gradient(t_point *p1, t_point *p2, int x)
{
	float	percent;
	int		red;
	int		green;
	int		blue;

	if (p1->color == p2->color)
		return (p1->color);
	if (p1->draw_x == p2->draw_x)
		return (p1->color);
	percent = (float)(x - p1->draw_x) / (p2->draw_x - p1->draw_x);
	red = (int)((p1->color >> 16) + percent * ((p2->color >> 16)
				- (p1->color >> 16)));
	green = (int)((p1->color >> 8 & 0xFF) + percent * ((p2->color >> 8 & 0xFF)
				- (p1->color >> 8 & 0xFF)));
	blue = (int)((p1->color & 0xFF) + percent * ((p2->color & 0xFF)
				- (p1->color & 0xFF)));
	return ((red << 16) | (green << 8) | blue);
}

int	ft_link(t_fdf *fdf, t_point *p1, t_point *p2)
{
	t_bresenham	*bres;
	t_point		*temp;

	init_bresenham(&bres, p1, p2);
	temp = p1;
	while (1)
	{
		my_mlx_pixel_put(fdf, p1->draw_x, p1->draw_y, 
				create_gradient(temp, p2, p1->draw_x));
		if (p1->draw_x == p2->draw_x && p1->draw_y == p2->draw_y)
			break ;
		bres->e2 = bres->delta * 2;
		if (bres->e2 >= -bres->delta_y)
		{
			bres->delta -= bres->delta_y;
			p1->draw_x += bres->slope_x;
		}
		if (bres->e2 < bres->delta_x)
		{
			bres->delta += bres->delta_x;
			p1->draw_y += bres->slope_y;
		}
	}
}

int	fdf_link_points(t_fdf *fdf)
{
	t_point	*point;
	
	point = fdf->map->first;
	while (point)
	{
		if (point->right_point)
			ft_link(fdf, point, point->right_point);
		if (point->bottom_point)
			ft_link(fdf, point, point->bottom_point);
		point = point ->next;
	}
}