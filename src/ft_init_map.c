/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:55:02 by norabino          #+#    #+#             */
/*   Updated: 2025/03/13 17:24:59 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
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
	new_point->x = x * 20;
	new_point->y = y * 20;
	new_point->z = ft_get_z(all_points[x]);
	new_point->next = NULL;
	new_point->right_point = NULL;
	new_point->bottom_point = NULL;
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
	if (y == 0)
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

void	ft_finalize_map(t_fdf **fdf, t_point **prev_row, int y, char *line)
{
	free(prev_row);
	free(line);
	(*fdf)->map->lines = y;
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
		free(all_points);
		y++;
		line = get_next_line(fd);
	}
	ft_finalize_map(fdf, prev_row, y, line);
}

void	ft_print_map(t_map *map)
{
	t_point	*point;
	int		temp_y;

	point = map->first;
	temp_y = point->y;
	printf("y = %d	", point->y);
	while (point)
	{
		if (temp_y != point->y)
			printf("\n\ny = %d	", point->y);
		printf("(x = %d z = %d)	", point->x, point->z);
		temp_y = point->y;
		point = point->next;
	}
	printf("\n\nLINKS : \n");
	point = map->first;
	temp_y = point->y;
	while (point)
	{
		if (point->y != temp_y)
			printf("\n");
		printf("%d", point->z);
		if (point->right_point)
			printf(" ⭢ ");
		//if (point->bottom_point)
			//printf("⭣\n");
		temp_y = point->y;
		point = point->next;
	}
}

void	ft_init_map(t_fdf *fdf, char **av)
{
	ft_init_points(&fdf, av);
	//ft_print_map(map);
	//ft_free_all(map);
}