/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_offset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:30:43 by norabino          #+#    #+#             */
/*   Updated: 2025/03/17 08:49:06 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_offset	*ft_init_offset()
{
	t_offset	*off;

	off = malloc(sizeof(t_offset));
	if (!off)
		return (NULL);
	off->max_x = INT_MIN;
	off->max_y = INT_MIN;
	off->min_x = INT_MAX;
	off->min_y = INT_MAX;
	return (off);
}

void	calc_offset_top(t_fdf *fdf)
{
	t_point		*current;
	t_offset	*off;

	off = ft_init_offset();
	current = fdf->map->first;
	while (current)
	{
		current->draw_x = current->init_x * fdf->zoom;
		current->draw_y = current->init_y * fdf->zoom;
		if (current->draw_x > off->max_x)
			off->max_x = current->draw_x;
		if (current->draw_y > off->max_y)
			off->max_y = current->draw_y;
		if (current->draw_x < off->min_x)
			off->min_x = current->draw_x;
		if (current->draw_y < off->min_y)
			off->min_y = current->draw_y;
		current = current->next;
	}
	fdf->offset_x = (1920 - (off->max_x - off->min_x)) / 2 - off->min_x;
	fdf->offset_y = (1080 - (off->max_y - off->min_y)) / 2 - off->min_y;
}

void	calc_offset_parralel(t_fdf *fdf)
{
	t_offset	*off;
	t_point		*current;

	off = ft_init_offset();
	current = fdf->map->first;
	while (current)
	{
		current->draw_x = current->init_x * fdf->zoom;
		current->draw_y = current->init_z * fdf->zoom;
		if (current->draw_x > off->max_x)
			off->max_x = current->draw_x;
		if (current->draw_y > off->max_y)
			off->max_y = current->draw_y;
		if (current->draw_x < off->min_x)
			off->min_x = current->draw_x;
		if (current->draw_y < off->min_y)
			off->min_y = current->draw_y;
		current = current->next;
	}
	fdf->offset_x = (1920 - (off->max_x - off->min_x)) / 2 - off->min_x;
	fdf->offset_y = (1080 - (off->max_y - off->min_y)) / 2 - off->min_y;
}

void	calc_iso(t_fdf *fdf, t_point **current)
{
	float	scaled_x;
	float	scaled_y;
	float	scaled_z;

	scaled_x = (*current)->init_x * fdf->zoom;
	scaled_y = (*current)->init_y * fdf->zoom;
	scaled_z = (*current)->init_z * fdf->zoom;
	(*current)->draw_x = (scaled_x - scaled_y) * cos(0.523599);
	(*current)->draw_y = -scaled_z + (scaled_x +scaled_y) * sin(0.523599);
	(*current)->draw_z = scaled_z;
}

void	calc_offset_iso(t_fdf *fdf)
{
	t_offset	*off;
	t_point		*current;

	off = ft_init_offset();
	current = fdf->map->first;
	while (current)
	{
		calc_iso(fdf, &current);
		if (current->draw_x > off->max_x)
			off->max_x = current->draw_x;
		if (current->draw_y > off->max_y)
			off->max_y = current->draw_y;
		if (current->draw_x < off->min_x)
			off->min_x = current->draw_x;
		if (current->draw_y < off->min_y)
			off->min_y = current->draw_y;
		current = current->next;
	}
	fdf->offset_x = (1920 - (off->max_x - off->min_x)) / 2 - off->min_x;
	fdf->offset_y = (1080 - (off->max_y - off->min_y)) / 2 - off->min_y;
}

void	fdf_calc_offset(t_fdf *fdf)
{
	if (fdf->view == 0)
		calc_offset_top(fdf);
	else if (fdf->view == 1)
		calc_offset_iso(fdf);
	else if (fdf->view == 2)
		calc_offset_parralel(fdf);
}