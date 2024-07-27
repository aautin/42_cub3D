/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/27 16:31:26 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"
#include "map.h"
#include "utils.h"

void	free_identified_map(t_identified_map *map, int status)
{
	t_index	i;

	i = NO_INDEX;
	while (i <= F_INDEX)
	{
		if (status & index_to_status(i))
			free(map->surfaces[i]);
		i++;
	}
}

static void	erase_newlines(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] == '\n')
			{
				lines[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
}

static int	identify_map(t_identified_map *map, char **lines)
{
	int	new_status;
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (lines[i] != NULL)
	{
		if (is_area_beginning(lines[i]))
		{
			map->area_index = i;
			break ;
		}
		new_status = identify_line(map, lines[i], i, status);
		if (new_status == NOT_FOUND)
			return (status);
		status |= new_status;
		i++;
	}
	if (status != COMPLETE_STATUS || map->area_index == NOT_FOUND)
		printf(ERROR_MSG "The file given is incomplete or in disorder\n");
	return (status);
}

static int	identify_area(char **map_content, int area_index, char ***areaPtr)
{
	char	**new_ptr;
	int		area_size;

	area_size = 0;
	while (map_content[area_index + area_size] != NULL)
		area_size++;
	new_ptr = malloc((area_size + 1) * sizeof(char *));
	if (new_ptr == NULL)
	{
		perror("identify_area():malloc()");
		return (FAILURE);
	}
	area_size = 0;
	while (map_content[area_index + area_size] != NULL)
	{
		new_ptr[area_size] = map_content[area_index + area_size];
		area_size++;
	}
	new_ptr[area_size] = NULL;
	while (area_index-- > 0)
		free(map_content[area_index]);
	free(map_content);
	*areaPtr = new_ptr;
	return (SUCCESS);
}

int	init_identification(t_identified_map *map, char *map_file_name,
	char ***area)
{
	t_list		*data_elements;
	int const	fd = open_fd(map_file_name);
	int			status;
	char		**map_content;

	if (fd == -1)
		return (FAILURE);
	data_elements = fd_to_lst(fd);
	if (data_elements == NULL)
		return (FAILURE);
	map_content = (char **) lst_to_double_tab(data_elements, NULL);
	ft_lstclear(&data_elements, NULL);
	if (map_content == NULL)
		return (FAILURE);
	erase_newlines(map_content);
	status = identify_map(map, map_content);
	if (status == COMPLETE_STATUS && map->area_index != NOT_FOUND
		&& identify_area(map_content, map->area_index, area) == SUCCESS)
		return (SUCCESS);
	free_double_tab((void **) map_content, -1);
	free_identified_map(map, status);
	return (FAILURE);
}
