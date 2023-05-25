/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:51:00 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/25 19:36:59 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	text_init(t_my_struct *m, t_map *t)
{
	int	i;
	int	j;

	m->t.n_img = mlx_xpm_file_to_image(m->mlx_ptr, t->no, &i, &j);
	m->t.w_img = mlx_xpm_file_to_image(m->mlx_ptr, t->we, &i, &j);
	m->t.o_img = mlx_xpm_file_to_image(m->mlx_ptr, t->ea, &i, &j);
	m->t.s_img = mlx_xpm_file_to_image(m->mlx_ptr, t->so, &i, &j);
	if (!m->t.s_img || !m->t.n_img || !m->t.o_img || !m->t.w_img)
		err_arg(ERR_FA_CONV);
}

void	window(t_my_struct *m, t_map *map)
{
	m->mlx_ptr = mlx_init();
	m->win_ptr = mlx_new_window(m->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	data_struct_init(m);
	text_init(m, map);
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
	draw(m);
	rander(m);
	update(m);
	mlx_clear_window(m->mlx_ptr, m->win_ptr);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->imge.img, 0, 0);
	return (0);
}
