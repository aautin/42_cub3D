/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/07/03 19:50:53 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"
#include "mlx.h"
#include "player.h"
#include "window.h"

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

void	freeGame(void *mlx, t_window *window, t_formattedMap *map, t_handlerParam *param)
{
	freeFormattedMap(mlx, map);
	mlx_destroy_window(mlx, window->obj);
	mlx_destroy_display(mlx);
	free(mlx);
	free(param);
}

int	main(int argc, char **argv)
{
	if (checkArgv(argc, argv) == FAILURE)
		return EXIT_FAILURE;

	void *mlx = mlx_init();
	if (mlx == NULL)
	{
		perror("main():mlx_init()");
		return EXIT_FAILURE;
	}

	t_formattedMap map;
	if (initFormattedMap(mlx, &map, argv[1]) == FAILURE)
	{
		freeGame(mlx, NULL, NULL, NULL);
		return EXIT_FAILURE;
	}

	t_player player;
	initPlayer(&player, &map);
	cleanArea(map.area, map.xSize);

	t_window window;
	if (initWindow(mlx, &window) == FAILURE)
	{
		freeGame(mlx, NULL, &map, NULL);
		return EXIT_FAILURE;
	}
	t_handlerParam *handlersParam = malloc(sizeof(*handlersParam));
	handlersParam->mlx = mlx;
	handlersParam->map = &map;
	handlersParam->player = &player;
	handlersParam->window = &window;
	initWindowHooks(handlersParam);

	mlx_loop(mlx);
	freeGame(mlx, &window, &map, handlersParam);
	return EXIT_SUCCESS;
}
