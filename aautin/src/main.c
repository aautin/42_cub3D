/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/07/11 14:53:11 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"
#include "mlx.h"
#include "player.h"
#include "cub3D.h"

static int	checkArgv(int argc, char **argv)
{
	if (argc != 2)
	{
		printf(ERROR_MSG "Wrong number of arguments\n");
		return FAILURE;
	}

	char *fileExtension = ft_strrchr(argv[1], '.');
	if (fileExtension == argv[1] || fileExtension == NULL)
	{
		printf(ERROR_MSG "File name is incorrect\n");
		return FAILURE;
	}
	if (ft_strncmp(fileExtension, ".cub", 5) != 0)
	{
		printf(ERROR_MSG "File name has a wrong extension\n");
		return FAILURE;
	}
	return SUCCESS;
}

static void	free_ptr_allocations(t_objs *objs, t_map *map, t_player *player)
{
	free(objs);
	free(map);
	free(player);
}

int	main(int argc, char **argv)
{
	if (checkArgv(argc, argv) == FAILURE)
		return EXIT_FAILURE;

	t_objs *objs = malloc(sizeof(t_objs));
	t_map *map = malloc(sizeof(t_map));
	t_player *player = malloc(sizeof(t_player));
	if (objs == NULL || map == NULL || player == NULL)
	{
		free_ptr_allocations(objs, map, player);
		return perror("main():malloc()"), EXIT_FAILURE;
	}

	t_vars *vars = malloc(sizeof(t_vars));
	if (vars == NULL || init_vars(vars) == FAILURE)
	{
		free(vars);
		free_ptr_allocations(objs, map, player);
		return EXIT_FAILURE;
	}

	if (initFormattedMap(vars->mlx, map, argv[1], player) == FAILURE)
	{
		free_ptr_allocations(objs, map, player);
		free_vars(vars);
		return EXIT_FAILURE;
	}

	if (init_objs(objs, vars, player, map) == FAILURE)
	{
		free_map(vars->mlx, map);
		free_vars(vars);
		return EXIT_FAILURE;
	}

	init_hooks(objs);
	mlx_loop(vars->mlx);
	free_objs(objs);
	return EXIT_SUCCESS;
}
