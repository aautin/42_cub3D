/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedParts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:59:55 by aautin            #+#    #+#             */
/*   Updated: 2024/06/19 23:41:28 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"

int seemToBeCode(char *line)
{
	return ft_strchr("CF", line[0]) != NULL && line[1] == ' ';
}

int	seemToBeTexture(char *line)
{
	if (ft_strnstr(line, "NO", 2) && line[2] == ' ')
		return 1;
	if (ft_strnstr(line, "SO", 2) && line[2] == ' ')
		return 1;
	if (ft_strnstr(line, "WE", 2) && line[2] == ' ')
		return 1;
	if (ft_strnstr(line, "EA", 2) && line[2] == ' ')
		return 1;
	return 0;
}

int	seemToBeArea(char letter)
{
	return ft_strchr("10NSWE", letter) != NULL;
}

int	identifyCode(t_identifiedMap *map, char *line, int letter)
{
	int	i = 0;
	while (line[i] == ' ')
		i++;
	line = &line[i];
	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	if (i != 0)
	{
		if (letter == 'C')
			letter = C_INDEX;
		else if (letter == 'F')
			letter = F_INDEX;
		map->code[letter] = ft_calloc((i + 1), sizeof(char));
		if (map->code[letter] == NULL)
			return (perror("identifyCode():ft_calloc()"), 0);
		while (i--)
			map->code[letter][i] = line[i];
		if (letter == C_INDEX)
			return C_CODE;
		return F_CODE;
	}
	printf("%s\nNo RGB-code after %c identifier\n", ERROR_MSG, letter);
	return 0;
}

static int	getCorrespondant(int code)
{
	if (code == 'N')
		return NORTH_INDEX;
	if (code == 'S')
		return SOUTH_INDEX;
	if (code == 'W')
		return WEST_INDEX;
	if (code == 'E')
		return EAST_INDEX;

	if (code == NORTH_INDEX)
		return NO_TEXTURE;
	if (code == SOUTH_INDEX)
		return SO_TEXTURE;
	if (code == WEST_INDEX)
		return WE_TEXTURE;
	if (code == EAST_INDEX)
		return EA_TEXTURE;
	return 0;
}

int	identifyTexture(t_identifiedMap *map, char *line, int letter, int nextLetter)
{
	int	i = 0;
	while (line[i] == ' ')
		i++;
	line = &line[i];
	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	if (i != 0)
	{
		letter = getCorrespondant(letter);
		map->texturesFilename[letter] = ft_calloc((i + 1), sizeof(char));
		if (map->texturesFilename[letter] == NULL)
			return (perror("identifyTexture():ft_calloc()"), 0);
		while (i--)
			map->texturesFilename[letter][i] = line[i];
		if (letter == C_INDEX)
			return C_CODE;
		return getCorrespondant(letter);
	}
	printf("%s\nNo texture-path after %c%c identifier\n", ERROR_MSG, letter, nextLetter);
	return 0;
}
