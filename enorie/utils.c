/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:05:28 by root              #+#    #+#             */
/*   Updated: 2024/07/05 13:38:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_numbers(char **numbers)
{
	int	i;
	int	j;

	i = 0;
	while (numbers[i])
	{
		j = 0;
		while (numbers[i][j] && ((numbers[i][j] >= 9 && numbers[i][j] <= 13)
			|| numbers[i][j] == 32))
			j++;
		if (!numbers[i][j] || !ft_isdigit(numbers[i][j]))
			return (1);
		i++;
	}
	if (i > 3)
		return (1);
	return (0);
}

int	ft_allnum(char *ligne)
{
	int	i;

	i = 0;
	if (ligne[i] == '\n')
		return (1);
	while (ligne[i] && (((ligne[i] >= 9 && ligne[i] <= 13)
				|| ligne[i] == 32) || ft_isalnum(ligne[i])))
	{
		while (ft_isalnum(ligne[i]))
			i++;
		while (ligne[i] && (((ligne[i] >= 9 && ligne[i] <= 13)
					|| ligne[i] == 32) || ft_isalnum(ligne[i])))
			i++;
	}
	if (ligne[i] && ligne[i] != '\n')
		return (1);
	return (0);
}

char	**ft_get_map_size(int fd, char *ligne)
{
	char	**map;
	char	*ligne2;
	int		i;

	i = 0;
	ligne2 = ligne;
	while (ligne2 && !ft_allnum(ligne2))
	{
		i++;
		free(ligne2);
		ligne2 = get_next_line(fd);
	}
	free(ligne2);
	map = malloc(sizeof(char *) * (i + 1));
	return (map);
}

int	ft_get_color_numbers(int *color, char *ligne)
{
	char	**numbers;

	numbers = ft_split(ligne + 1, ',');
	if (!numbers)
		return (1);
	if (ft_check_numbers(numbers))
		return (1);
	*color = ft_create_trgb(0, ft_atoi(numbers[0]),
			ft_atoi(numbers[1]), ft_atoi(numbers[2]));
	ft_free_numbers(numbers);
	return (0);
}

int	ft_get_texture_path(char *ligne, t_vars *vars, t_data *data)
{
	ligne++;
	ligne++;
	while (*ligne && ((*ligne >= 9 && *ligne <= 13) || *ligne == 32))
		ligne++;
	ligne[ft_strlen(ligne) - 1] = '\0';
	data->img = mlx_xpm_file_to_image(vars->mlx, ligne,
			&data->width, &data->height);
	if (!data->img)
		return (1);
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits_pixel,
			&data->line_length, &data->endian);
	return (0);
}
