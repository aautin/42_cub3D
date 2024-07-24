/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedLine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/24 04:03:46 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "map.h"
#include "utils.h"

static int	get_surface_index(char *identifier)
{
	const int	identifier_len = ft_strlen(identifier);

	if (identifier_len > 2)
		return (NOT_FOUND);
	if (identifier_len == 1)
	{
		if (*identifier == 'C')
			return (C_INDEX);
		return (F_INDEX);
	}
	if (identifier[0] == 'N' && identifier[1] == 'O')
		return (NO_INDEX);
	if (identifier[0] == 'S' && identifier[1] == 'O')
		return (SO_INDEX);
	if (identifier[0] == 'W' && identifier[1] == 'E')
		return (WE_INDEX);
	if (identifier[0] == 'E' && identifier[1] == 'A')
		return (EA_INDEX);
	return (NOT_FOUND);
}

int	is_area_beginning(char *line)
{
	while (*line == ' ')
		line++;
	return (line[0] != '\0' && ft_strchr("10", line[0]) != NULL);
}

static int	identify_components(t_identified_map *map, char **components,
	int line_index, int status)
{
	int		surface_i;
	char	*surface_complement;

	if (!components[0] || !components[1] || components[2])
		surface_i = NOT_FOUND;
	else
		surface_i = get_surface_index(components[0]);
	if (surface_i == NOT_FOUND || (status & index_to_status(surface_i)))
		return (printf(ERROR_MSG "Line %d incorrect\n", line_index + 1),
			NOT_FOUND);
	if (status & index_to_status(surface_i))
	{
		free(map->surfaces[surface_i]);
		status = status ^ index_to_status(surface_i);
		printf(ERROR_MSG "Line %d incorrect\n", line_index + 1);
		return (NOT_FOUND);
	}
	surface_complement = ft_strdup(components[1]);
	if (surface_complement == NULL)
	{
		perror("identify_line():ft_strdup()");
		return (NOT_FOUND);
	}
	map->surfaces[surface_i] = surface_complement;
	return (index_to_status(surface_i));
}

int	identify_line(t_identified_map *map, char *line, int line_index, int status)
{
	int		new_status;
	char	**line_components;

	if (line[0] == '\0')
		return (0);
	line_components = ft_split(line, ' ');
	if (line_components == NULL)
		return (perror("identifyMap():ft_split()"), NOT_FOUND);
	new_status = identify_components(map, line_components, line_index, status);
	free_double_tab((void **) line_components, -1);
	return (new_status);
}
