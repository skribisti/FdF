/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:44:33 by norabino          #+#    #+#             */
/*   Updated: 2025/03/26 17:07:09 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img->addr)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	fdf_coords_in_window(float x, float y)
{
	if (x < 0 || x >= 1920)
		return (0);
	if (y < 0 || y >= 1080)
		return (0);
	return (1);
}

void	calc_iso(t_fdf *fdf, t_point **current)
{
	float	scaled_x;
	float	scaled_y;
	float	scaled_z;

	if (!current || !(*current))
		return ;
	scaled_x = (*current)->init_x * fdf->zoom;
	scaled_y = (*current)->init_y * fdf->zoom;
	scaled_z = (*current)->init_z * fdf->zoom;
	(*current)->draw_x = (scaled_x - scaled_y) * cos(0.523599);
	(*current)->draw_y = -scaled_z + (scaled_x + scaled_y) * sin(0.523599);
}

void	ft_uppercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}
