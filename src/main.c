/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/07/26 07:15:36 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"
#include "mlx.h"
#include "player.h"
#include "cub3D.h"

static int	check_argv(int argc, char **argv)
{
	char	*file_extension;

	if (argc != 2)
	{
		printf(ERROR_MSG "Wrong number of arguments\n");
		return ((FAILURE));
	}
	file_extension = ft_strrchr(argv[1], '.');
	if (file_extension == argv[1] || file_extension == NULL)
	{
		printf(ERROR_MSG "File name is incorrect\n");
		return ((FAILURE));
	}
	if (ft_strncmp(file_extension, ".cub", 5) != 0)
	{
		printf(ERROR_MSG "File name has a wrong extension\n");
		return ((FAILURE));
	}
	return ((SUCCESS));
}

static void	free_ptr_allocations(t_vars *vars, t_objs *objs, t_map *map, t_player *player)
{
	if (vars != NULL && vars->mlx != NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
	free(vars);
	free(objs);
	free(map);
	free(player);
	vars = NULL;
	objs = NULL;
	map = NULL;
	player = NULL;
}

static void	ptr_allocations(t_vars **vars, t_objs **objs, t_map **map, t_player **player)
{
	*objs = malloc(sizeof(t_objs));
	*map = malloc(sizeof(t_map));
	*player = malloc(sizeof(t_player));
	*vars = malloc(sizeof(t_vars));
	if (*vars)
		(*vars)->mlx = NULL;
}

int	main(int argc, char **argv)
{
	t_objs		*objs;
	t_map		*map;
	t_player	*player;
	t_vars		*vars;

	if (check_argv(argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	ptr_allocations(&vars, &objs, &map, &player);
	if (objs == NULL || map == NULL || player == NULL || vars == NULL)
		return (free_ptr_allocations(vars, objs, map, player),
			perror("main():malloc()"), EXIT_FAILURE);
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (perror("init_vars():mlx_init()"), free_ptr_allocations(vars,
				objs, map, player), EXIT_FAILURE);
	if (init_formatted_map(vars->mlx, map, argv[1], player) == FAILURE)
		return (free_ptr_allocations(vars, objs, map, player), EXIT_FAILURE);
	if (init_vars(vars) == FAILURE)
		return (free_map(vars->mlx, map), free_ptr_allocations(vars, objs, map,
			player), EXIT_FAILURE);
	if (init_objs(objs, vars, player, map) == FAILURE)
		return (free_map(vars->mlx, map), free_vars(vars), EXIT_FAILURE);
	init_hooks(objs);
	mlx_loop(vars->mlx);
	return (free_objs(objs), EXIT_SUCCESS);
}
