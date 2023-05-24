/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loops_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:04:37 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/24 23:45:50 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	space_fill(char *line, int max, char *uncheck)
{
	size_t	i;

	i = 0;
	while (i < (size_t)max)
	{
		if (i > ft_strlen(uncheck) - 1 || uncheck[i] == '\n')
			line[i] = ' ';
		i++;
	}
}

void	fill_cond(char *line, int i, int *dupe, char *uncheck)
{
	if (ft_strlen(uncheck) > 1)
	{
		if (line[i] == 'E' || line[i] == 'W'
			|| line[i] == 'S' || line[i] == 'N')
		{
			if (!(*dupe))
				*dupe |= 1 << 0;
			else
				*dupe |= 1 << 1;
		}
		if ((line[i] != ' ' && line[i] != '1' && line[i] != '0'
				&& line[i] != 'N' && line[i] != 'W'
				&& line[i] != 'S' && line[i] != 'E')
			|| (line[0] != '1' && line[0] != ' ')
			|| (line[ft_strlen(uncheck) - 2] != '1'
				&& line[ft_strlen(uncheck) - 2] != ' '))
			*dupe |= 1 << 2;
	}
	else if (ft_strlen(uncheck) == 1)
	{
		if (line[0] != '1' && line[0] != ' ')
			*dupe |= 1 << 2;
	}
}

void	fill_rest(char *line, int max, int *dupe, char *uncheck)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		fill_cond(line, i, dupe, uncheck);
		i++;
	}
	space_fill(line, max, uncheck);
}

int	within_walls(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == 'E' || map[i][j] == 'W'
		|| map[i][j] =='S' || map[i][j] == 'N')
	{
		if (map[i - 1][j] == ' '
			|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '
			|| map[i + 1][j] == ' ')
			return (0);
	}
	return (1);
}

int	check_ends(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}
