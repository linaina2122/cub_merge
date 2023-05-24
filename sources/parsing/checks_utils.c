/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:08:00 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/24 23:44:54 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *feature, char *ext)
{
	if (ft_strncmp((feature + ft_strlen(feature) - ft_strlen(ext)), ext, 5))
		return (1);
	return (0);
}

int	check_file(char *file)
{
	int	i;

	i = open(file, O_DIRECTORY);
	if (i > 0)
	{
		close(i);
		return (1);
	}
	i = open(file, O_RDONLY, 0644);
	if (i == -1)
		return (1);
	close(i);
	return (0);
}

int	check_nums(char **feature)
{
	int	i;

	i = -1;
	while (feature[++i] != NULL)
	{
		if (ft_color_atoi(feature[i]) == -1)
			return (1);
	}
	return (0);
}

char	**check_end_spaces(char *line, int *flags)
{
	char	*trim;
	char	**split;

	trim = ft_strtrim(line, " \t");
	split = ft_split(trim, ' ');
	if (split[0] && split[1])
	{
		if (split[2] && ft_strncmp(split[2], "\n", 2))
		{
			free(trim);
			trim = ft_strtrim(split[2], " \n\t");
			if (ft_strncmp(trim, "\0", 1))
				*flags ^= 1 << 6;
		}
	}
	free(trim);
	return (split);
}

int	empty_line(char *line, int *dimh, int *dimw)
{
	int	i;

	i = -1;
	while (ft_isempty(line[++i]))
		;
	if (ft_isempty(line[i]) && *dimh)
		return (1);
	else if ((!ft_isempty(line[i]) && line[i]))
	{
		*dimh += 1;
		if ((size_t)*dimw < ft_strlen(line))
			*dimw = ft_strlen(line);
		return (0);
	}
	return (1);
}