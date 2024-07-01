/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/07/01 20:56:44 by aautin           ###   ########.fr       */
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

void	freeGame(void *mlx, t_window *window, t_formattedMap *map)
{
	if (map && mlx)
		freeFormattedMap(mlx, map);
	if (window && mlx)
		mlx_destroy_window(mlx, window);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
}

void	printArea(char **area)
{
	for (int i = 0; area[i] != NULL; i++)
	{
		printf("%s\n", area[i]);
	}
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
		freeGame(mlx, NULL, NULL);
		return EXIT_FAILURE;
	}

	t_window window;
	if (initWindow(&window, mlx) == FAILURE)
	{
		freeGame(mlx, NULL, &map);
		return EXIT_FAILURE;
	}

	cleanArea(map.area, map.xSize);
	printArea(map.area);
	mlx_loop(mlx);
	freeGame(mlx, &window, &map);
	return EXIT_SUCCESS;
}
