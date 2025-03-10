/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/10 10:01:48 by norabino         ###   ########.fr       */
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

int	handle_close(t_vars *vars)
{
	printf("Window closed using the red cross button.\n");
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}

int	mouse_hook(int keycode, t_vars *vars)
{
	if (keycode == 1)
		printf("Hello from key_hook\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_data	img;
	t_vars	vars;
	int		color;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	color = create_trgb(100, 0, 122, 122);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	my_mlx_pixel_put(&img, 50, 50, color);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 17, 0, handle_close, &vars);
	mlx_loop(vars.mlx);

	if (!ft_check_args(ac, av))
		return (1);
	ft_init_map(av);
	//fdf(ac, av);
	return(0);
}
