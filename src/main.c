/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/24 11:11:41 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (!ft_check_args(ac, av))
		return (1);
	fdf = ft_init_fdf_and_img();
	ft_init_map(fdf, av);
	if (!fdf)
		return (1);
	if (verif_all_ok(fdf))
	{
		fdf_draw(fdf, fdf->view);
		mlx_hook(fdf->win, 17, 1L << 17, handle_close, fdf);
		mlx_hook(fdf->win, 2, 1L << 0, handle_hook, fdf);
		mlx_loop(fdf->mlx);
	}
	handle_close(fdf);
	return (0);
}
