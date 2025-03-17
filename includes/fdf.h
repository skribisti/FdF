/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:23:37 by norabino          #+#    #+#             */
/*   Updated: 2025/03/17 09:38:22 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx_linux/mlx.h"
# include "../libft/includes/libft.h"
# include "get_next_line.h"
# include "stdio.h"
# include "stdlib.h"
# include "fcntl.h"
# include "math.h"

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_offset
{
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;
}	t_offset;

typedef struct s_point
{
	int				init_x;
	int				init_y;
	int				init_z;
	int				draw_x;
	int				draw_y;
	int				draw_z;
	int				color;
	struct s_point	*right_point;
	struct s_point	*bottom_point;
	struct s_point	*next;
}	t_point;

typedef struct s_map
{
	struct s_point	*first;
	int				collums;
	int				lines;
}	t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_map	*map;
	float	zoom;
	int		offset_x;
	int		offset_y;
	int		view;
	int		switch_view;
}	t_fdf;

// FDF
int fdf(int ac, char **av);
t_fdf	*ft_init_fdf_and_img();

//MLX
int	init_window_img(t_fdf *fdf);
int	verif_all_ok(t_fdf *fdf);

// HOOK
int	handle_hook(int keycode, t_fdf *fdf);
void	handle_keycode(int keycode, t_fdf *fdf);
int	handle_close(t_fdf *fdf);

// DRAW
int		fdf_draw(t_fdf *fdf, int view);
void	draw_top(t_fdf *fdf);

// OFFSET
void	fdf_calc_offset(t_fdf *fdf);

// LINK


// CHECK ARGS
int	ft_check_args(int ac, char **av);
int	ft_check_open(char **av);
char *ft_take_extension(char **av);
int	ft_strcmp(char *str1, char *str2);

// MAP
void	ft_init_map(t_fdf *fdf,char **av);
void	ft_free_map(t_map *map);

// SPLIT
char	**ft_split(char const *str, char c);

#endif