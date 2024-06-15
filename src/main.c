/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/06/15 23:52:58 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extended.h"
#include "mlx.h"
#include "mlx_int.h"

#define MAP_FILE_NAME			"simpleMap.cub"

#define STEP_LENGHT				0.1
#define DIR_LENGHT				1
#define PLANE_LENGHT			2 * DIR_LENGHT
// here "2 * DIR_LENGHT" sets a 90' FOV

#define DESTROY_WINDOW_EVENT	17
#define DESTROY_WINDOW_MASK		0

#define KEY_PRESSED_EVENT		2
#define KEY_PRESSED_MASK		(1L<<0)

#define ESC_KEYCODE				65307

#define	A_KEYCODE_LEFT			97
#define	D_KEYCODE_RIGHT			100
#define	S_KEYCODE_DOWN			115
#define	W_KEYCODE_UP			119

typedef struct s_window {
	void *obj;
	int xSize;
	int ySize;
}	t_window;
void	initWindow(t_window *window, void *obj, int xSize, int ySize)
{
	window->obj = obj;
	window->xSize = xSize;
	window->ySize = ySize;
}

typedef struct s_player {
	int xPosition;
	int yPosition;
	float xDirection;
	float yDirection;
	float xCasePosition;
	float yCasePosition;
}	t_player;
void	initPlayer(t_player *player, int xPosition, int yPosition)
{
	player->xPosition = xPosition;
	player->yPosition = yPosition;
	player->xDirection = -1;
	player->yDirection = 0;
	player->xCasePosition = 0.5;
	player->yCasePosition = 0.5;
}

typedef struct s_map {
	char	**content;
	int		xSize;
	int		ySize;
}	t_map;
void	initMap(t_map *map, char *mapFileName)
{
	int fd = open(mapFileName, O_RDONLY);

	t_list *mapRows;
	mapRows = NULL;

	char *row = get_next_line(fd);
	map->xSize = 0;
	while (row)
	{
		ft_lstadd_front(&mapRows, ft_lstnew(row));
		map->xSize++;
		row = get_next_line(fd);
	}
	map->ySize = ft_strlen(mapRows->content);
	map->content = malloc(map->xSize * sizeof(char *));

	int rowIndex = 0;
	while (rowIndex < map->xSize)
	{
		map->content[rowIndex] = mapRows->content;
		mapRows = mapRows->next;
		rowIndex++;
	}
}

int	isKeycodeMakingPlayerMove(int keycode, t_map *map, t_player *player)
{
	int xPotentialPosition, yPotentialPosition;
	switch (keycode)
	{
		case A_KEYCODE_LEFT :
			xPotentialPosition = player->xPosition + (int)(player->xCasePosition + (player->yDirection * STEP_LENGHT));
			yPotentialPosition = player->yPosition + (int)(player->yCasePosition + (player->xDirection * STEP_LENGHT));
			break;
		case D_KEYCODE_RIGHT :
			xPotentialPosition = player->xPosition + (int)(player->xCasePosition - (player->yDirection * STEP_LENGHT));
			yPotentialPosition = player->yPosition + (int)(player->yCasePosition - (player->xDirection * STEP_LENGHT));
			break;
		case W_KEYCODE_UP :
			xPotentialPosition = player->xPosition + (int)(player->xCasePosition + (player->xDirection * STEP_LENGHT));
			yPotentialPosition = player->yPosition + (int)(player->yCasePosition + (player->yDirection * STEP_LENGHT));
			break;
		case S_KEYCODE_DOWN :
			xPotentialPosition = player->xPosition + (int)(player->xCasePosition - (player->xDirection * STEP_LENGHT));
			yPotentialPosition = player->yPosition + (int)(player->yCasePosition - (player->yDirection * STEP_LENGHT));
			break;
		default :
			xPotentialPosition = player->xPosition;
			yPotentialPosition = player->yPosition;
			break;
	}
	return map->content[yPotentialPosition][xPotentialPosition] == '0';
}

void	modifyPlayerPosition(int keycode, t_player *player)
{
	switch (keycode)
	{
		case A_KEYCODE_LEFT :
			player->xPosition -= player;
			player->xCasePosition = (player->xCasePosition + (player->yDirection * STEP_LENGHT)) - 1;
			player->xCasePosition = (player->yCasePosition + (player->xDirection * STEP_LENGHT)) - 1;
			break;
		case D_KEYCODE_RIGHT :
			player->xPosition++;
			player->xCasePosition = (player->xCasePosition + (player->xDirection * STEP_LENGHT)) - 1;
			break;
		case W_KEYCODE_UP :
			player->yPosition--;
			break;
		case S_KEYCODE_DOWN :
			player->yPosition++;
			break;
		default :
			break;
	}
}

typedef struct s_keyHandlerParam {
	t_window	*window;
	t_player	*player;
	t_map		*map;
	void		*mlx;
}	t_keyHandlerParam;
void	initKeyHandlerParam(t_keyHandlerParam *param, t_window *window, t_map *map, t_player *player, void *mlx)
{
	param->window = window;
	param->player = player;
	param->map = map;
	param->mlx = mlx;
}
int	keyHandler(int keycode, t_keyHandlerParam *param)
{	
	if (keycode == ESC_KEYCODE)
		mlx_loop_end(param->mlx);
	else if (isKeycodeMakingPlayerMove(keycode, param->map, param->player))
	{
		modifyPlayerPosition(keycode, param->player);
		ft_printf("player's position: %dx*%dy\n",
				param->player->xPosition, param->player->yPosition);
	}
	return 0;
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	void *mlx = mlx_init();
	if (mlx == NULL)
		return 1;

	int	xScreenSize, yScreenSize;
	mlx_get_screen_size(mlx, &xScreenSize, &yScreenSize);
	if (xScreenSize <= DIR_LENGHT * 2 || yScreenSize <= DIR_LENGHT * 2)
		return 0;

	void *windowObj = mlx_new_window(mlx, xScreenSize, yScreenSize, "cub3d: top_view");

	t_window window;
	initWindow(&window, windowObj, xScreenSize, yScreenSize);

	t_map map;
	initMap(&map, MAP_FILE_NAME);

	t_player player;
	initPlayer(&player, map.xSize / 2, map.ySize / 2);

	t_keyHandlerParam param;
	initKeyHandlerParam(&param, &window, &player, mlx);

	mlx_hook(window.obj, KEY_PRESSED_EVENT, KEY_PRESSED_MASK, &keyHandler, &param);
	mlx_hook(window.obj, DESTROY_WINDOW_EVENT, DESTROY_WINDOW_MASK, &mlx_loop_end, mlx);

	mlx_loop(mlx);

	return 0;
}
