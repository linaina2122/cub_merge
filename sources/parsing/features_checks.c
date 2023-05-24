/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:57:20 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/23 06:35:08 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*shift_textures(char *feature, int *flags, int n)
{
	char	*dup;

	dup = NULL;
	*flags ^= 1 << n;
	if (check_extension(feature, EXT_XPM) || check_file(feature))
	{
		*flags |= 1 << 6;
		free(feature);
		return (NULL);
	}
	dup = ft_strdup(feature);
	free(feature);
	return (dup);
}

int	num_commas(char *feature)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (feature[++i])
	{
		if (feature[i] == ',')
			cnt++;
	}
	if (cnt != 2)
		return (1);
	return (0);
}

unsigned int	*shift_colors(char *feature, int *flags, int n)
{
	char				**colors;
	unsigned int		*rgb;

	*flags ^= 1 << n;
	colors = ft_split(feature, ',');
	if (len_darr(colors) != 3 || check_nums(colors) || num_commas(feature))
	{
		*flags |= 1 << 6;
		free(feature);
		free_darr(colors);
		return (NULL);
	}
	rgb = (unsigned int *)malloc(sizeof(int));
	*rgb = (ft_color_atoi(colors[0]) << 16)
		| (ft_color_atoi(colors[1]) << 8) | (ft_color_atoi(colors[2]));
	free(feature);
	free_darr(colors);
	return (rgb);
}

void	check_feat_dupes(char *feature, int *flags)
{
	if (!ft_strncmp(feature, "NO", 3) && ((*flags & 32) == 0))
		*flags ^= 1 << 6;
	else if (!ft_strncmp(feature, "SO", 3) && (*flags & 16) == 0)
		*flags ^= 1 << 6;
	else if (!ft_strncmp(feature, "WE", 3) && (*flags & 8) == 0)
		*flags ^= 1 << 6;
	else if (!ft_strncmp(feature, "EA", 3) && (*flags & 4) == 0)
		*flags ^= 1 << 6;
	else if (!ft_strncmp(feature, "C", 2) && (*flags & 2) == 0)
		*flags ^= 1 << 6;
	else if (!ft_strncmp(feature, "F", 2) && (*flags & 1) == 0)
		*flags ^= 1 << 6;
}

void	check_each(char *line, int *flags, t_map *map)
{
	char	**split;

	split = check_end_spaces(line, flags);
	check_feat_dupes(split[0], flags);
	if (!ft_strncmp(split[0], "NO", 3) && ((*flags & 32) == 32))
		map->no = shift_textures(ft_strtrim(split[1], " \t\n"), flags, 5);
	else if (!ft_strncmp(split[0], "SO", 3) && (*flags & 16) == 16)
		map->so = shift_textures(ft_strtrim(split[1], " \t\n"), flags, 4);
	else if (!ft_strncmp(split[0], "WE", 3) && (*flags & 8) == 8)
		map->we = shift_textures(ft_strtrim(split[1], " \t\n"), flags, 3);
	else if (!ft_strncmp(split[0], "EA", 3) && (*flags & 4) == 4)
		map->ea = shift_textures(ft_strtrim(split[1], " \t\n"), flags, 2);
	else if (!ft_strncmp(split[0], "C", 2) && (*flags & 2) == 2)
		map->c = shift_colors(ft_strtrim(split[1], " \t\n"), flags, 1);
	else if (!ft_strncmp(split[0], "F", 2) && (*flags & 1) == 1)
		map->f = shift_colors(ft_strtrim(split[1], " \t\n"), flags, 0);
	free_darr(split);
}