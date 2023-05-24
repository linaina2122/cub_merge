/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:55:55 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/24 23:46:47 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(char **map, t_map_tools *ts, int height)
{
	ts->i = 0;
	while (++ts->i < height - 1)
	{
		ts->j = 1;
		while (map[ts->i][ts->j])
		{
			if (!within_walls(map, ts->i, ts->j))
				return (1);
			ts->j++;
		}
	}
	return (check_ends(map[0]) || check_ends(map[height - 1]));
}

void	final_map(char **layout, size_t *x, size_t *y, double *sdir)
{
	int	i;
	int	j;

	i = -1;
	while (layout[++i])
	{
		j = -1;
		while (layout[i][++j])
		{
			if (layout[i][j] == ' ')
				layout[i][j] = '1';
			if (layout[i][j] == 'N' || layout[i][j] == 'S'
				|| layout[i][j] == 'W' || layout[i][j] == 'E')
			{
				*x = i;
				*y = j;
				*sdir = player_orientation(layout[i][j]);
			}
		}
	}
}

void	map_loop(t_map *map)
{
	while (map->tools->line)
	{
		if (empty_line(map->tools->line, &map->dim[0], &map->dim[1]))
		{
			if (map->dim[0])
				break ;
			free(map->tools->line);
			map->tools->line = get_next_line(map->tools->fd);
			continue ;
		}
		map->tools->unchecked_map = ft_realloc(map->tools->unchecked_map,
				(map->dim[0] + 1) * sizeof(char *));
		map->tools->unchecked_map[map->dim[0] - 1]
			= ft_strdup(map->tools->line);
		free(map->tools->line);
		map->tools->line = get_next_line(map->tools->fd);
	}
}

void	map_cond_loop(t_map *map)
{
	if (map->tools->unchecked_map)
	{
		map->tools->unchecked_map[map->dim[0]] = NULL;
		map->layout = (char **)malloc(sizeof(char *) * (map->dim[0] + 1));
		map->tools->i = 0;
		while (map->tools->i < map->dim[0])
		{
			map->layout[map->tools->i]
				= (char *)malloc(sizeof(char) * (map->dim[1]));
			ft_memmove(map->layout[map->tools->i],
				map->tools->unchecked_map[map->tools->i], map->dim[1] - 1);
			map->layout[map->tools->i][map->dim[1] - 1] = '\0';
			fill_rest(map->layout[map->tools->i],
				map->dim[1] - 1, &map->tools->dupe,
				map->tools->unchecked_map[map->tools->i]);
			map->tools->i++;
		}
		map->layout[map->tools->i] = NULL;
		free_darr(map->tools->unchecked_map);
	}
}

int	check_scene(char *file, t_map *map)
{
	map->tools->dupe = 0;
	map->tools->flags = 63;
	map->dim[0] = 0;
	map->dim[1] = 0;
	map->tools->fd = open(file, O_RDONLY, 0644);
	map->tools->line = get_next_line(map->tools->fd);
	map->tools->unchecked_map = NULL;
	while (map->tools->line && map->tools->flags != 0)
	{
		if (map->tools->flags <= 63 && map->tools->flags)
			check_each(map->tools->line, &map->tools->flags, map);
		free(map->tools->line);
		map->tools->line = get_next_line(map->tools->fd);
	}
	map_loop(map);
	map_cond_loop(map);
	free(map->tools->line);
	close(map->tools->fd);
	if (map->tools->flags || map->dim[0] < 3 || map->dim[1] < 4
		|| map->tools->dupe != 1
		|| check_map(map->layout, map->tools, map->dim[0]))
		return (-1);
	final_map(map->layout, &map->pos[0], &map->pos[1], &map->s_dir);
	return (0);
}