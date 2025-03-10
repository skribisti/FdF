/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:26:20 by norabino          #+#    #+#             */
/*   Updated: 2025/03/10 14:49:56 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#define WIDTH 1920
#define HEIGHT 1080

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

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	(void)vars;
	if (keycode == 1)
		printf("Mouse clicked %d %d\n", x, y);
	return (0);
}

int	color_screen(t_vars *vars, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(vars->img, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int	update(t_vars *vars)
{
	
	if (vars->frame_count >= 60)
	{
		vars->frame_count = 0;
		if (vars->color == create_trgb(0, 255, 0, 0))
			vars->color = create_trgb(0, 0, 255, 0);
		else if (vars->color == create_trgb(0, 0, 255, 0))
			vars->color = create_trgb(0, 0, 0, 255);
		else if (vars->color == create_trgb(0, 0, 0, 255))
			vars->color = create_trgb(0, 255, 0, 0);
	}
	color_screen(vars, vars->color);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	vars->frame_count++;
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;


	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	vars.img->img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img->addr = mlx_get_data_addr(vars.img->img, &vars.img->bits_per_pixel, &vars.img->line_length,
								&vars.img->endian);
	vars.frame_count = 0;
	vars.color = create_trgb(0, 255, 0, 0);
	//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 17, 0, handle_close, &vars);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_loop(vars.mlx);

	if (!ft_check_args(ac, av))
		return (1);
	ft_init_map(av);
	//fdf(ac, av);
	return(0);
}
