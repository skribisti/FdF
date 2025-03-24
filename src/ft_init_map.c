/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:55:02 by norabino          #+#    #+#             */
/*   Updated: 2025/03/24 12:23:46 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	return (new_point);
}

t_point	*ft_create_point(t_data *data, char **all_points, int x, int y)
{
	t_point	*new_point;
	t_map	*map;
	t_point	**tail;

	new_point = ft_init_coords_point(all_points, x, y);
	map = (data->fdf)->map;
	tail = data->tail;
	if (!map->first)
		map->first = new_point;
	if (*tail)
		(*tail)->next = new_point;
	*tail = new_point;
	return (new_point);
}

void	ft_process_line(t_data *data, char **all_points, int y)
{
	t_point	*current;
	int		x;
	int		cols;
	t_point	**prev_row;

	x = 0;
	cols = ft_count_cols(all_points);
	prev_row = *(data->prev_row);
	if (y == 0)
		prev_row = ft_realloc_prev_row(prev_row, cols);
	while (x < cols)
	{
		current = ft_create_point(data, all_points, x, y);
		if (x > 0)
			prev_row[x - 1]->right_point = current;
		if (y > 0)
			prev_row[x]->bottom_point = current;
		prev_row[x] = current;
		x++;
	}
	*(data->prev_row) = prev_row;
}

int	ft_init_points(t_fdf *fdf, char **av, char *line, int fd)
{
	t_point	*tail;
	t_point	**prev_row;
	char	**all_points;
	int		y;
	t_data	data;

	fdf->map->first = NULL;
	tail = NULL;
	prev_row = NULL;
	y = 0;
	fd = open(av[1], O_RDONLY);
	data.fdf = fdf;
	data.tail = &tail;
	data.prev_row = &prev_row;
	line = get_next_line(fd);
	while (line)
	{
		all_points = ft_split(line, ' ');
		ft_process_line(&data, all_points, y);
		free_split(all_points);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	return (free(prev_row), free(line), close(fd), 0);
}

void	ft_init_map(t_fdf *fdf, char **av)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = 0;
	fdf->map = (t_map *)malloc(sizeof(t_map));
	if (!fdf->map)
		return ;
	(void)ft_init_points(fdf, av, line, fd);
}
