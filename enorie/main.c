/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:52:34 by enorie            #+#    #+#             */
/*   Updated: 2024/07/06 15:30:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_find_pos(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	while (all->map->map[i])
	{
		j = 0;
		while (all->map->map[i][j])
		{
			j++;
			if (all->map->map[i][j] == 'N' || all->map->map[i][j] == 'W'
				|| all->map->map[i][j] == 'E' || all->map->map[i][j] == 'S')
			{
				all->pos->x = j + 0.5;
				all->pos->y = i + 0.5;
				ft_get_pos(all->map->map, i, j, all->pos);
			}
		}
		i++;
	}
}

int	ft_get_config(char *path, t_map *map, t_vars *vars)
{
	char	*ligne;
	char	*ligne2;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_puterror("File does not exist\n"));
	ligne = get_next_line(fd);
	while (ligne && ft_allnum(ligne))
	{
		ligne2 = ligne;
		while (*ligne && ((*ligne >= 9 && *ligne <= 13) || *ligne == 32))
			ligne++;
		if (ft_choose(map, ligne, vars))
			return (close(fd), free(ligne2), 1);
		if (ft_choose2(map, ligne))
			return (close(fd), free(ligne2), 1);
		free(ligne2);
		ligne = get_next_line(fd);
	}
	if (!map->no || !map->so || !map->ea || !map->we
		|| ft_get_map(fd, map, ligne, path))
		return (close(fd), 1);
	close(fd);
	return (0);
}

void	ft_cubed(t_all *all)
{
	int			x;

	all->data->img = mlx_new_image(all->vars->mlx, all->vars->sizex,
			all->vars->sizey);
	all->data->addr = (int *)mlx_get_data_addr(all->data->img,
			&all->data->bits_pixel, &all->data->line_length,
			&all->data->endian);
	x = 0;
	while (x < all->vars->sizex)
	{
		ft_raycast1(all->rc, all, x);
		ft_raycast2(all->rc, all->pos);
		while (all->rc->hit == 0)
			ft_raycast3(all->rc, all->map);
		ft_raycast4(all->rc, all);
		ft_draw(all->rc, all, x);
		x++;
	}
	mlx_put_image_to_window(all->vars->mlx, all->vars->win,
		all->data->img, 0, 0);
	mlx_destroy_image(all->vars->mlx, all->data->img);
}

int	ft_check_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] != '\n')
		{
			while (!ft_isalnum(map->map[i][j]))
				j++;
			if (map->map[i][j] != '\n' && map->map[i][j] != '1')
				return (ft_puterror("Wrong map"));
			while (map->map[i][j] != '\n' && ft_isalnum(map->map[i][j]))
			{
				if (map->map[i][j] != '1' && map->map[i][j] != '0'
					&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
					&& map->map[i][j] != 'E' && map->map[i][j] != 'W')
					return (ft_puterror("Wrong map"));
				j++;
			}
			if (map->map[i][j - 1] != '1')
				return (ft_puterror("Wrong map"));
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all		*all;

	if (argc != 2)
	{
		printf("Not enough args\n");
		return (1);
	}
	all = ft_init_strucks();
	if (!all)
		return (ft_puterror("Can't create strucks\n"));
	all->vars->mlx = mlx_init();
	if (ft_get_config(argv[1], all->map, all->vars) || ft_check_map(all->map))
		return (ft_free_all(all), 1);
	ft_find_pos(all);
	mlx_get_screen_size(all->vars->mlx, &(all->vars)->sizex,
		&(all->vars)->sizey);
	all->vars->win = mlx_new_window(all->vars->mlx, all->vars->sizex,
			all->vars->sizey, "Cub3D");
	ft_cubed(all);
	mlx_hook(all->vars->win, 2, 1L << 0, key_hook, all);
	mlx_hook(all->vars->win, 17, 0, end, all->vars);
	mlx_loop(all->vars->mlx);
	return (ft_free_all(all), 0);
}
