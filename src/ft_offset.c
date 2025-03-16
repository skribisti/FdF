/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_offset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:30:43 by norabino          #+#    #+#             */
/*   Updated: 2025/03/16 14:29:18 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_init_offset(t_offset *off)
{
	off->max_x = INT_MIN;
	off->max_y = INT_MIN;
	off->min_x = INT_MAX;
	off->min_y = INT_MIN;
}

void	calc_offset_top(t_fdf *fdf);

void	ft_calc_offset(t_fdf *fdf)
{
	if (fdf->view == 0)
		calc_offset_top(fdf);
	/*else if (fdf->view == 1)
		calc_offset_iso(fdf);
	else if (fdf->view == 2)
		calc_offset_parralel(fdf);*/
}