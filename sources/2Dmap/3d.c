/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:50:07 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/24 19:36:46 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void text_initttt(t_my_struct *m)
{
	if(m->r->is_it_verticale)
	{
		if(check_left_right(m->r->rayangle))
			m->t.addr = mlx_get_data_addr(m->t.w_img, &m->t.bpp, &m->t.line_length, &m->t.endian);
		else
			m->t.addr = mlx_get_data_addr(m->t.o_img, &m->t.bpp, &m->t.line_length, &m->t.endian);
	}
	else
	{
		if(check_up_down(m->r->rayangle))
			m->t.addr = mlx_get_data_addr(m->t.n_img, &m->t.bpp, &m->t.line_length, &m->t.endian);
		else
			m->t.addr = mlx_get_data_addr(m->t.s_img, &m->t.bpp, &m->t.line_length, &m->t.endian);
	}
}

void	rander(t_my_struct *m)
{
	int		count;
	double	ray_angle;

	count = 0;
	ray_angle = m->r->rayangle - (FOV_ANGLE / 2);
	ray_angle = normalize_angle(ray_angle);	
	while (count < NUM_RAYS)
	{
		text_initttt(m);
		h_intercept(m, ray_angle);
		v_intercept(m, ray_angle);
		m->r->is_it_verticale = 0;
		get_distance(m);
		renderwalls(m, ray_angle);
		walls(m, count);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		ray_angle = normalize_angle(ray_angle);
		count++;
	}
}

unsigned int	ft_get_pixel(t_text m, int x, int y)
{
	int		offset;

	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return 0;
	offset = (y * m.line_length) + (x * m.bpp/8);
	unsigned int a = *((unsigned int *)(m.addr + offset));
	return(a);
}



void	walls(t_my_struct *m, int count)
{
	float	top_of_wall;
	float end_of_wall;
	int x;
	int y = 0;
	top_of_wall = (HEIGHT / 2) - (m->r->wallstrip / 2);
	end_of_wall = (HEIGHT / 2) + (m->r->wallstrip / 2);
	if(m->r->is_it_verticale == 1)
		x = (int)m->r->vwally % SCALE;
	else 
		x = (int)m->r->howallx % SCALE;
	while (top_of_wall < end_of_wall)
	{
		y = (top_of_wall + (m->r->wallstrip / 2) - (HEIGHT / 2)) *  (SCALE / m->r->wallstrip);
		ft_put_pixel(m, count, top_of_wall, ft_get_pixel(m->t, x, y));
		top_of_wall++;
	}
}

void	renderwalls(t_my_struct *m, double ray_angle)
{
	double	disprojectionplane;
	double	correctwalldist;

	correctwalldist = (float)(m->r->final_distance) * cos(ray_angle\
			- m->rot_angle);
	disprojectionplane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	m->r->wallstrip = 0.3 * ((SCALE / correctwalldist) * disprojectionplane);
}
