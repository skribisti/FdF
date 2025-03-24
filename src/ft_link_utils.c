/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:08:56 by norabino          #+#    #+#             */
/*   Updated: 2025/03/24 11:11:12 by norabino         ###   ########.fr       */
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

void	check_colors(int colors[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (colors[i] < 0)
			colors[i] = 0;
		if (colors[i] > 255)
			colors[i] = 255;
		i++;
	}
}

void	ft_calc_colors(t_point *p1, t_point *p2, int rgb[3], float percent)
{
	rgb[0] = (int)((p1->color >> 16) + percent * ((p2->color >> 16)
				- (p1->color >> 16)));
	rgb[1] = (int)((p1->color >> 8 & 0xFF) + percent
			* ((p2->color >> 8 & 0xFF) - (p1->color >> 8 & 0xFF)));
	rgb[2] = (int)((p1->color & 0xFF) + percent
			* ((p2->color & 0xFF) - (p1->color & 0xFF)));
	check_colors(rgb);
}
