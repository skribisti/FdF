/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:12:53 by norabino          #+#    #+#             */
/*   Updated: 2025/03/14 10:02:23 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	verif_all_ok(t_fdf *fdf)
{
	if (fdf->img && fdf->img->img && fdf->mlx && fdf->win)
		return (1);
	return (0);
}

void	ft_free_map(t_fdf *fdf)
{
	t_point	*current;
	t_point *tmp;

	current = fdf->map->first;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(fdf->map);
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
		ft_free_map(fdf);
	if (fdf->img)
		free(fdf->img);
    exit(0);
	return (0);
}

void	handle_keycode(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		handle_close(fdf);
	else if (keycode == 65364)
		;//fdf->zoom *= 0.9;
	else if (keycode == 65362)
		;//fdf->zoom *= 1.1;
	if (keycode == 115 || keycode == 100 || keycode == 97 || keycode == 119)
		change_offset(keycode, fdf);
}

int	handle_hook(int keycode, t_fdf *fdf)
{
	handle_keycode(keycode, fdf);
	mlx_destroy_image(fdf->mlx, fdf->img->img);
	fdf->img->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->img->addr = mlx_get_data_addr(fdf->img->img,
		&fdf->img->bits_per_pixel, &fdf->img->line_length, &fdf->img->endian);
	fdf_draw(fdf);
}
