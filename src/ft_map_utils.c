/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:53:43 by norabino          #+#    #+#             */
/*   Updated: 2025/03/26 17:06:58 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_get_z(char *coords)
{
	int		i;
	int		res;
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
	int		i;
	int		j;
	int		color;
	char	*sub;

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
	ft_uppercase(sub);
	color = ft_atoi_base(sub, "0123456789ABCDEF");
	free(sub);
	return (color);
}
