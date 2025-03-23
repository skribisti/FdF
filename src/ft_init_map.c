/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:55:02 by norabino          #+#    #+#             */
/*   Updated: 2025/03/23 16:16:01 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_get_z(char *coords)
{
	int	i;
	int	res;
	char	*sub;
	
	i = 0;
	while (coords[i] && coords[i] != '\n' && coords[i] != ',')
		i++;
	sub = ft_substr(coords, 0, i);
	res = ft_atoi(sub);
	free (sub);
	return (res);
}

int	ft_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	if (base[i] && base[i] == c)
		return (1);
	return (0);
}

int	ft_ismaj(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_atoi_base(const char *nptr, char *base)
{
	int		res;
	int		i;
	char	*str;

	str = (char *)nptr;
	i = 0;
	res = 0;
	while (str[i] && ft_in_base(str[i], base))
	{
		res *= ft_strlen(base);
		if (ft_isdigit(str[i]))
			res += str[i] - '0';
		else if (ft_ismaj(str[i]))
			res += str[i] - 55;
		i++;
	}
	return (res);
}

int	ft_get_color(char *coords)
{
	int	i;
	int	j;
	int	color;
	char *sub;

	i = 0;
	while (coords[i] && coords[i] != '\n' && coords[i] != ',')
		i++;
	j = i + 3;
	if (coords[i] == ',')
	{
		while (coords[j])
			j++;
	}
	if (j == i + 3)
		return (create_trgb(1, 255, 255, 255));
	sub = ft_substr(coords, i + 3, j);
	color = ft_atoi_base(sub, "0123456789ABCDEF");
	free (sub);
	return (color);
}

t_point	**ft_realloc_prev_row(t_point **prev_row, int cols)
{
	t_point	**new_row;
	int		i;

	new_row = malloc(cols * sizeof(t_point *));
	if (!new_row)
		return (NULL);
	i = 0;
	while (i < cols)
	{
		new_row[i] = NULL;
		i++;
	}
	if (prev_row)
		free(prev_row);
	return (new_row);
}

int	ft_count_cols(char **all_points)
{
	int	count;

	count = 0;
	while (all_points[count])
		count++;
	return (count);
}

t_point	*ft_init_coords_point(char **all_points, int x, int y)
{
	t_point	*new_point;

	new_point = (t_point *)malloc(sizeof(t_point));
	if (!new_point)
		return (NULL);
	new_point->init_x = x * 20;
	new_point->init_y = y * 20;
	new_point->init_z = ft_get_z(all_points[x]);
	new_point->color = ft_get_color(all_points[x]);
	new_point->next = NULL;
	new_point->right_point = NULL;
	new_point->bottom_point = NULL;
	//ft_printf("%d, %d, %d\n", new_point->init_x, new_point->init_y, new_point->init_x);
	return (new_point);
}

t_point	*ft_create_point(t_map *map, t_point **tail,
			char **all_points, int x, int y)
{
	t_point	*new_point;

	new_point = ft_init_coords_point(all_points, x, y);
	if (!(map)->first)
		(map)->first = new_point;
	if (*tail)
		(*tail)->next = new_point;
	*tail = new_point;
	return (new_point);
}

void	ft_process_line(t_fdf **fdf, t_point **tail,
			t_point ***prev_row, char **all_points, int y)
{
	t_point	*current;
	int		x;
	int		cols;

	x = 0;
	cols = ft_count_cols(all_points);
	//if (y == 0)
	*prev_row = ft_realloc_prev_row(*prev_row, cols);
	while (x < cols)
	{
		current = ft_create_point((*fdf)->map, tail, all_points, x, y);
		if (x > 0)
			(*prev_row)[x - 1]->right_point = current;
		if (y > 0)
			(*prev_row)[x]->bottom_point = current;
		(*prev_row)[x] = current;
		x++;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_init_points(t_fdf **fdf, char **av)
{
	t_point	*tail;
	t_point	**prev_row;
	char	*line;
	char	**all_points;
	int		fd;
	int		y;

	(*fdf)->map->first = NULL;
	tail = NULL;
	prev_row = NULL;
	y = 0;
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		all_points = ft_split(line, ' ');
		ft_process_line(fdf, &tail, &prev_row, all_points, y);
		free_split(all_points);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	free(line);
}

void	ft_free_map(t_map *map)
{
	t_point	*current;
	t_point	*temp;

	if (map->first)
	{
		current = map->first;
		while (current)
		{
			temp = current->next;
			free(current);
			current = temp;
		}
		free(map);
	}
}

void	ft_init_map(t_fdf *fdf, char **av)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return ;
	fdf->map = map;
	ft_init_points(&fdf, av);
}