/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:23:37 by norabino          #+#    #+#             */
/*   Updated: 2025/03/11 15:25:14 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx_linux/mlx.h"
# include "get_next_line.h"
# include "stdio.h"
# include "stdlib.h"
# include "fcntl.h"

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
	struct s_point	*right_point;
	struct s_point	*bottom_point;
	struct s_point	*next;
}	t_point;

typedef struct s_map
{
	struct s_point	*first;
	int		collums;
	int		lines;
}	t_map;

typedef struct s_fdf
{
	t_img	*img;
	void	*vars;
	t_map	*map;
	float	zoom;
}	t_fdf;

// FDF
int fdf(int ac, char **av);

//MLX
int	init_window_img(t_fdf *fdf, t_vars *vars, t_img *img);

// DRAW
int	draw_points(t_fdf *fdf, t_vars *vars, t_img *img);

// LINK


// CHECK ARGS
int	ft_check_args(int ac, char **av);
int	ft_check_open(char **av);
char *ft_take_extension(char **av);
int	ft_strcmp(char *str1, char *str2);
int	ft_strlen(char *str);

// INIT MAP
void	ft_init_map(t_fdf *fdf,char **av);

// SPLIT
char	**ft_split(char const *str, char c);

#endif