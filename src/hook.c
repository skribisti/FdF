/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:12:53 by norabino          #+#    #+#             */
/*   Updated: 2025/03/17 11:19:38 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	verif_all_ok(t_fdf *fdf)
{
	if (fdf->img && fdf->img->img && fdf->mlx && fdf->win)
		return (1);
	return (0);
}

int	handle_close(t_fdf *fdf)
{
	if (fdf->mlx && fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->img && fdf->img->img)
		mlx_destroy_image(fdf->mlx, fdf->img->img);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		fdf->mlx = NULL;
	}
	if (fdf->map && fdf->map->first)
		ft_free_map(fdf->map);
	if (fdf->img)
		free(fdf->img);
    exit(0);
	return (0);
}

void	change_offset(int keycode, t_fdf *fdf);

void	handle_keycode(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		handle_close(fdf);
	else if (keycode == 65364)
		ft_printf("zoom out\n");//fdf->zoom *= 0.9;
	else if (keycode == 65362)
		ft_printf("zoom in\n");//fdf->zoom *= 1.1;
	else if (keycode == 115 || keycode == 100 || keycode == 97 || keycode == 119)
		ft_printf("move\n");//change_offset(keycode, fdf);
}

int	handle_hook(int keycode, t_fdf *fdf)
{
	fdf->switch_view = 1;
	handle_keycode(keycode, fdf);
	if (fdf->img && fdf->img->img)
		mlx_destroy_image(fdf->mlx, fdf->img->img);
	fdf->img->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img,
		&fdf->img->bits_per_pixel, &fdf->img->line_length, &fdf->img->endian);
	if (verif_all_ok(fdf))
		return (fdf_draw(fdf, fdf->view), 0);
	return (1);
}
