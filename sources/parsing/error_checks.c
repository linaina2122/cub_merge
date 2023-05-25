/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:28:37 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/25 20:01:29 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_arg(char *custom_err_msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(custom_err_msg, 2);
	exit(0);
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

void	init_parse(t_map *map)
{
	map->tools = (t_map_tools *)malloc(sizeof(t_map_tools));
	map->c = NULL;
	map->f = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->so = NULL;
	map->no = NULL;
	map->layout = NULL;
}

void	game_main(t_map *map)
{
	t_my_struct	*s;

	s = malloc(sizeof(t_my_struct));
	s->map = map->layout;
	s->r = malloc(sizeof(t_ray));
	s->rot_angle = map->s_dir;
	s->flag = 0;
	s->move[0] = 0;
	s->move[1] = 0;
	s->move[2] = 0;
	player_init(s);
	s->ceil_col = *map->c;
	s->speed = 2 * (M_PI_2 / 180);
	s->fov_angle = 60 * (M_PI_2 / 180);
	s->floor_col = *map->f;
	s->map_width = map->dim[1] - 1;
	s->map_height = map->dim[0];
	window(s, map);
}

int	main(int ac, char **av)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	init_parse(map);
	error_checks(ac, av, map);
	game_main(map);
	return (0);
}