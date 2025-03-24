/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:03:52 by norabino          #+#    #+#             */
/*   Updated: 2025/03/24 10:08:58 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_count_cols(char **all_points)
{
	int	count;

	count = 0;
	while (all_points[count])
		count++;
	return (count);
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
