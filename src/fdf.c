/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/06 16:50:32 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*int fdf(int ac, char **av)
{
	ac = 0;
	av[0][0] = 0;
	printf("allo");
	return (0);
}*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;
	int		color;

	if (!ft_check_args(ac, av))
		return (1);
	ft_init_map(av);
	(void)mlx_window;
	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color = create_trgb(100, 0, 122, 122);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 50, 50, color);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	mlx_loop(mlx);
	//fdf(ac, av);
	return(0);
}
