/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/07/11 12:29:26 by root             ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	if (checkArgv(argc, argv) == FAILURE)
		return EXIT_FAILURE;

	t_vars *vars = malloc(sizeof(t_vars));
	if (init_vars(vars) == FAILURE)
		return EXIT_FAILURE;

	t_player *player = malloc(sizeof(t_player));
	t_map *map = malloc(sizeof(t_map));
	if (initFormattedMap(vars->mlx, map, argv[1], player) == FAILURE)
	{
		free_vars(vars);
		return EXIT_FAILURE;
	}

	t_objs *objs = malloc(sizeof(t_objs));
	if (init_objs(objs, vars, player, map) == FAILURE)
	{
		free_map(vars->mlx, map);
		free_vars(vars);
		return EXIT_FAILURE;
	}

	init_hooks(objs);
	mlx_loop(vars->mlx);
	return EXIT_SUCCESS;
}
