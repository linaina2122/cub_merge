/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:51:00 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/23 13:42:04 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_height(t_my_struct *m)
{
	int i;

	 i = 0;
	while(m->map[i])
		i++;
	return (i);
}
int	ft_get_width(t_my_struct *m)
{
	int i;

	i = 1;
	int j = 0;
	while(m->map[i])
	{
		if(m->map[i] && m->map[i - 1] && ft_strlen(m->map[i]) >= ft_strlen(m->map[i - 1]))
			j = ft_strlen(m->map[i]);
		i++;
	}
	return (j);
}


void get_map_width_and_height(t_my_struct *m)
{
	m->map_width = ft_get_width(m);
	m->map_height = ft_get_height(m);
}


void	window(t_my_struct *m)
{
	
	get_map_width_and_height(m);
	m->mlx_ptr = mlx_init();
	m->win_ptr = mlx_new_window(m->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	data_struct_init(m);
	loop_func(m);

	mlx_hook(m->win_ptr, ON_KEYDOWN, 0, mouvements_press, m);
	mlx_hook(m->win_ptr, ON_KEYUP, 0, mouvements_release, m);
	mlx_hook(m->win_ptr, ON_DESTROY, 0, exiting, m);
	mlx_loop_hook(m->mlx_ptr, loop_func, m);
	mlx_loop(m->mlx_ptr);
}


int	loop_func(t_my_struct *m)
{
	m->r->rayangle = normalize_angle(m->rot_angle);
	iterater(m);
	draw(m);
	rander(m);
	update(m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->imge.img, 0, 0);
	return (0);
}
