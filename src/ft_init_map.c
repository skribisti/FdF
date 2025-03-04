/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:55:02 by norabino          #+#    #+#             */
/*   Updated: 2025/03/04 16:49:19 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/get_next_line.h"

int	ft_isdigit(char c)
{
	if (c > '0' && c < '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int		res;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}
int	ft_get_z(char *coords)
{
	int	i;
	
	i = 0;
	while (coords[i] && coords[i] != '\n' && coords[i] != ',')
		i++;
	return (ft_atoi(ft_substr(coords, 0, i)));
}

/*int	ft_get_color(char *coords)
{
	char *z_content;
	
	if (ft_strchr(coords, ','))
		z_content = ft_strchr(coords, ',');
	
}*/

void	ft_init_point_iter(t_point **current, char **all_points_in_line, int *x, int y)
{
	(*current) = (t_point *)malloc(sizeof(t_point *));
	(*current)->x = *x;
	(*current)->y = y;
	(*current)->z = ft_get_z(all_points_in_line[*x]);
	//current->color = ft_get_color(all_points_in_line[x]);
	(*x)++;
}

void	ft_init_points(t_map **map, char **av)
{
	t_point	*current;
	char	*line;
	char	**all_points_in_line;
	int		fd;
	int		x;
	int		y;

	//(*map)->first = (t_point *)malloc(sizeof(t_point *));
	current = (*map)->first;
	y = 0;
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		all_points_in_line = ft_split(line, ' ');
		x = 0;
		while(all_points_in_line[x])
			ft_init_point_iter(&current, all_points_in_line, &x, y);
		y++;
		line = get_next_line(fd);
	}
	free(line);
	free(all_points_in_line);
	//ft_print_map()
}

void	ft_init_map(char **av)
{
	t_map	*map;
	
	map = (t_map *)malloc(sizeof(t_map *));
	if (!map)
		return ;
	ft_init_points(&map, av);
	printf("fini");
	//ft_free_all(map);
}