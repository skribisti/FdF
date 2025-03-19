/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:59:13 by norabino          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:37 by norabino         ###   ########.fr       */
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

int	fdf_coords_in_window(t_point	*point)
{
	if ((point->draw_x < 0 || point->draw_x > 1920) || (point->draw_y < 0 || point->draw_y > 1080))
		return (0);
	return (1);
}

void	draw_top(t_fdf *fdf)
{
	t_point	*current;

	if (!fdf->map)
		return ;
	if ((fdf->offset_x == 0 && fdf->offset_y == 0) || (fdf->switch_view))
		fdf_calc_offset(fdf);
	current = fdf->map->first;
	while (current)
	{
		current->draw_x = current->init_x * fdf->zoom + fdf->offset_x;
		current->draw_y = current->init_y * fdf->zoom + fdf->offset_y;
		if (fdf_coords_in_window(current))
			my_mlx_pixel_put(fdf->img, current->draw_x, current->draw_y, create_trgb(1, 255, 255, 255));
		current = current->next;
	}
}

void	draw_iso(t_fdf *fdf)
{
	t_point	*current;
	float	scale_x;
	float	scale_y;

	if (!fdf->map)
		return ;
	if ((!fdf->offset_x && fdf->offset_y) || (fdf->switch_view))
		fdf_calc_offset(fdf);
	current = fdf->map->first;
	while (current)
	{
		scale_x = current->init_x * fdf->zoom;
		scale_y = current->init_y * fdf->zoom;
		current->draw_x = (scale_x - scale_y) * cos(0.53599) + fdf->offset_x;
		current->draw_y = (scale_x + scale_y) * sin(0.523599)
			- (current->init_z * fdf->zoom) + fdf->offset_y;
		if (fdf_coords_in_window(current))
			my_mlx_pixel_put(fdf->img, current->draw_x, current->draw_y, create_trgb(1, 255, 255, 255));
		current = current->next;
	}
}

void	draw_parralel(t_fdf *fdf)
{
	t_point	*current;

	if (!fdf->map)
		return ;
	if ((fdf->offset_x == 0 && fdf->offset_y == 0) || (fdf->switch_view))
		fdf_calc_offset(fdf);
	current = fdf->map->first;
	while (current)
	{
		current->draw_x = current->init_x * fdf->zoom + fdf->offset_x;
		current->draw_y = -current->init_z * fdf->zoom + fdf->offset_y;
		if (fdf_coords_in_window(current))
			my_mlx_pixel_put(fdf->img, current->draw_x, current->draw_y, create_trgb(1, 255, 255, 255));
		current = current->next;
	}
}



int	fdf_draw(t_fdf *fdf, int view)
{
	if (view == 0)
		draw_iso(fdf);
	else if (view == 1)
		draw_parralel(fdf);
	else if (view == 2)
		draw_top(fdf);
	//fdf_link_points(fdf);
	if (!verif_all_ok(fdf))
		return (ft_printf("Image non valide\n"),1);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->img, 0, 0);
	return (0);	
}