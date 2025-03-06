/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:23:37 by norabino          #+#    #+#             */
/*   Updated: 2025/03/06 08:50:07 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../mlx_linux/mlx.h"
# include "get_next_line.h"
# include "stdio.h"
# include "stdlib.h"
# include "fcntl.h"

typedef struct s_map
{
	struct s_point	*first;
	int				collums;
	int				rows;
}	t_map;

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

// FDF
int fdf(int ac, char **av);

// CHECK ARGS
int	ft_check_args(int ac, char **av);
int	ft_check_open(char **av);
char *ft_take_extension(char **av);
int	ft_strcmp(char *str1, char *str2);
int	ft_strlen(char *str);

// INIT MAP
void	ft_init_map(char **av);

// SPLIT
char	**ft_split(char const *str, char c);

#endif