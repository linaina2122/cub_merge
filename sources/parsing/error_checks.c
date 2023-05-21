/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:28:37 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/21 15:50:38 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_arg(char *custom_err_msg)
{
	ft_putstr_fd(custom_err_msg, 2);
	// system("leaks cub3D");
	exit(0);
}
//! Annoying makefile 

void	free_darr(char **darr)
{
	size_t	i;

	i = 0;
	while (darr[i])
	{
		// printf("%s", darr[i]);
		free(darr[i]);
		i++;
	}
	free(darr);
}

void	free_map(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->c)
		free(map->c);
	if (map->f)
		free(map->f);
	if (map->layout)
		free_darr(map->layout);
	free(map->tools);
	free(map);
}

//* or simmply:
//*return (ft_strncmp((feature + ft_strlen(feature) - ft_strlen(ext)), ext, 5))?
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


int	len_darr(char **darr)
{
	int	i;

	i = -1;
	while (darr[++i])
		;
	return (i);
}

//! need to check for MAXINT and MININT in ft_color_atoi
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

char	*shift_textures(char	*feature, int *flags, int n)
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

int	*shift_colors(char *feature, int *flags, int n)
{
	char	**colors;
	int		*rgb;

	*flags ^= 1 << n;
	colors = ft_split(feature, ',');
	if (len_darr(colors) != 3 || check_nums(colors))
	{
		*flags |= 1 << 6;
		free(feature);
		free_darr(colors);
		return (NULL);
	}
	rgb = (int *)malloc(sizeof(int));
	*rgb = (ft_color_atoi(colors[0]) << 16) | (ft_color_atoi(colors[1]) << 8) | (ft_color_atoi(colors[2]));
	free(feature);
	free_darr(colors);
	return (rgb);
}

void	check_each(char *line, int *flags, t_map *map)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!ft_strncmp(split[0], "NO", 3) && ((*flags & 32) == 32))
		map->no = shift_textures(ft_strtrim(split[1], " \n"), flags, 5);
	else if (!ft_strncmp(split[0], "SO", 3) && (*flags & 16) == 16)
		map->so = shift_textures(ft_strtrim(split[1], " \n"), flags, 4);
	else if (!ft_strncmp(split[0], "WE", 3) && (*flags & 8) == 8)
		map->we = shift_textures(ft_strtrim(split[1], " \n"), flags, 3);
	else if (!ft_strncmp(split[0], "EA", 3) && (*flags & 4) == 4)
		map->ea = shift_textures(ft_strtrim(split[1], " \n"), flags, 2);
	else if (!ft_strncmp(split[0], "C", 2) && (*flags & 2) == 2)
		map->c = shift_colors(ft_strtrim(split[1], " \n"), flags, 1);
	else if (!ft_strncmp(split[0], "F", 2) && (*flags & 1) == 1)
		map->f = shift_colors(ft_strtrim(split[1], " \n"), flags, 0);
	free_darr(split);
}


//? How to check the map inside the get_next_line loop?
//* first we calculate the dimensions of the map
//*		-> width is the length of the longest line
//*		-> height is how many lines are in the map
//! Constraints
//! the lines will either have to be stored in a -- TOBECONTINUED

int	empty_line(char *line, size_t *dimh, size_t *dimw)
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
		if (*dimw < ft_strlen(line))
			*dimw = ft_strlen(line);
		return (0);
	}
	return (1);
}

void	fill_rest(char *line, int max, int *dupe, char *uncheck) //*to fill up rest of line
{
	int	i;
	(void)uncheck;
	i = 0;	
	while (line[++i] && line[i] != '\n')
	{
		if (line[i] == 'E' || line[i] == 'W' || line[i] == 'S' || line[i] == 'N')
		{
			if (!(*dupe))
				*dupe |= 1 << 0;
			else
				*dupe |= 1 << 1;
		}
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'W' && line[i] != 'S' && line[i] != 'E')
			*dupe |= 1 << 2;
	}
	while(i < max)
	{
		if (line[i] == ' ' || line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'W' || line[i] == 'S' || line[i] == 'E')
			;
		else
			line[i] = ' ';
		i++;
	}
}

int	within_walls(char **map, size_t i, size_t j)
{

	if (map[i][j] == '0' || map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] =='S' || map[i][j] == 'N')
	{
		if (map[i-1][j-1] == ' ' || map[i-1][j] == ' ' || map[i-1][j+1] == ' '
		 || map[i][j-1] == ' ' || map[i][j+1] == ' '
		 || map[i+1][j-1] == ' ' || map[i+1][j] == ' ' || map[i+1][j+1] == ' ')
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

int	check_map(char **map, t_map_tools *ts, size_t height)
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

//* 63 is the decimal of 0011 1111 in binary,
//* 	each bit will correspond to a flag
//* left->right NO->SO->WE->EA->F->C
//? Might add more later to accomodate F & C textures if I fancy it
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
		map->tools->unchecked_map = ft_realloc(map->tools->unchecked_map, (map->dim[0] + 1) * sizeof(char *));
		map->tools->unchecked_map[map->dim[0] - 1] = ft_strdup(map->tools->line);
		free(map->tools->line);
		map->tools->line = get_next_line(map->tools->fd);
	}
	if (map->tools->unchecked_map)
	{
		map->tools->unchecked_map[map->dim[0]] = NULL;
		map->layout = (char **)malloc(sizeof(char *) * (map->dim[0] + 1));
		map->tools->i = 0;
		while (map->tools->i < map->dim[0])
		{
			map->layout[map->tools->i] = (char *)malloc(sizeof(char) * (map->dim[1]));
			ft_memmove(map->layout[map->tools->i], map->tools->unchecked_map[map->tools->i], map->dim[1] - 1);
			map->layout[map->tools->i][map->dim[1] - 1] = '\0';
			fill_rest(map->layout[map->tools->i], map->dim[1] - 1, &map->tools->dupe, map->tools->unchecked_map[map->tools->i]);
			map->tools->i++;
		}
		map->layout[map->tools->i] = NULL;
		free_darr(map->tools->unchecked_map);
	}
	free(map->tools->line);
	close(map->tools->fd);
	if (map->tools->flags || map->dim[0] < 3 || map->dim[1] < 4 || map->tools->dupe != 1 || check_map(map->layout, map->tools, map->dim[0]))
		return (-1);
	return (0);
}

//* int
void	error_checks(int ac, char **av, t_map *map)
{
	if (ac != 2)
		err_arg(ERR_NUM_ARG);
	if (check_file(av[1]))
		err_arg(ERR_OPN_FIL);
	if (check_extension(av[1], EXT_CUB))
		err_arg(ERR_WRG_EXT);
	if (check_scene(av[1], map))
	{
		free_map(map);
		err_arg(ERR_WRG_SCN);
	}
}

// void	game_main(t_map *map)
// {
// 	t_my_struct *s;

// 	s = my_fun();
// 	s->r = malloc(sizeof(t_ray));
// 	s->rot_angle = M_PI_2 / 3;
// 	s->move[0] = 0;
// 	s->move[1] = 0;
// 	s->move[2] = 0;
// 	player_init(s);
// 	window(s);
// }

int main(int ac, char **av)
{
	t_map	*map;
	
	// init_parse(&map);
	map = (t_map *)malloc(sizeof(t_map));
	map->tools = (t_map_tools *)malloc(sizeof(t_map_tools));
	map->c = NULL;
	map->f = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->so = NULL;
	map->no = NULL;
	map->layout = NULL;
	error_checks(ac, av, map);
	// game_main(map);
	free_map(map);
	return (0);
}