/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:01:16 by root              #+#    #+#             */
/*   Updated: 2024/07/09 01:15:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_get_map(int fd, t_map *map, char *ligne, char *path)
{
	int		i;
	int		fd2;
	char	*ligne2;

	map->map = ft_get_map_size(fd, ligne);
	if (!map->map)
		return (1);
	fd2 = open(path, O_RDONLY);
	ligne2 = get_next_line(fd2);
	while (ligne2 && ft_allnum(ligne2))
	{
		free(ligne2);
		ligne2 = get_next_line(fd2);
	}
	i = 0;
	while (ligne2 && !ft_allnum(ligne2))
	{
		map->map[i++] = ft_strdup(ligne2);
		free(ligne2);
		ligne2 = get_next_line(fd2);
	}
	map->map[i] = NULL;
	free(ligne2);
	close(fd2);
	return (0);
}

int	ft_choose(t_map *map, char *ligne, t_vars *vars)
{
	if (ligne && !ft_strncmp(ligne, "NO", 2))
		if (ft_get_texture_path(ligne, vars, map->no))
			return (1);
	if (ligne && !ft_strncmp(ligne, "SO", 2))
		if (ft_get_texture_path(ligne, vars, map->so))
			return (1);
	if (ligne && !ft_strncmp(ligne, "WE", 2))
		if (ft_get_texture_path(ligne, vars, map->we))
			return (1);
	if (ligne && !ft_strncmp(ligne, "EA", 2))
		if (ft_get_texture_path(ligne, vars, map->ea))
			return (1);
	return (0);
}

int	ft_choose2(t_map *map, char *ligne)
{
	if (ligne && *ligne == 'F')
		if (ft_get_color_numbers(&map->f, ligne))
			return (1);
	if (ligne && *ligne == 'C')
		if (ft_get_color_numbers(&map->c, ligne))
			return (1);
	return (0);
}

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_data	*ft_find_texture(int side, double raydirx, double raydiry, t_map *map)
{
	if (side == 0 && raydirx > 0)
		return (map->we);
	else if (side == 0 && raydirx < 0)
		return (map->ea);
	else if (side == 1 && raydiry > 0)
		return (map->no);
	else
		return (map->so);
}
