/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/07/08 00:35:11 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"
#include "mlx.h"

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

	void *mlx = mlx_init();
	if (mlx == NULL)
	{
		perror("main():mlx_init()");
		return EXIT_FAILURE;
	}

	t_formattedMap map;
	if (initFormattedMap(mlx, &map, argv[1]) == FAILURE)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return EXIT_FAILURE;
	}

	// ... include enorie's part there.
	freeFormattedMap(mlx, &map);
	mlx_destroy_display(mlx);
	free(mlx);
	return EXIT_SUCCESS;
}
