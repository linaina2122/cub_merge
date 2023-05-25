/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:50:07 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/25 19:53:23 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	text_initttt(t_my_struct *m, float ray_angle)
{
	if (m->r->is_it_verticale)
	{
		if (check_left_right(ray_angle))
			m->t.addr = (unsigned int *)mlx_get_data_addr(m->t.w_img, \
			&m->t.bpp, &m->t.line_length, &m->t.endian);
		else
			m->t.addr = (unsigned int *)mlx_get_data_addr(m->t.o_img, \
			&m->t.bpp, &m->t.line_length, &m->t.endian);
	}
	else
	{
		if (check_up_down(ray_angle))
			m->t.addr = (unsigned int *)mlx_get_data_addr(m->t.n_img, \
			&m->t.bpp, &m->t.line_length, &m->t.endian);
		else
			m->t.addr = (unsigned int *)mlx_get_data_addr(m->t.s_img, \
			&m->t.bpp, &m->t.line_length, &m->t.endian);
	}
}

void	rander(t_my_struct *m)
{
	int		count;
	double	ray_angle;

	count = 0;
	ray_angle = m->r->rayangle - (m->fov_angle / 2);
	ray_angle = normalize_angle(ray_angle);
	while (count < NUM_RAYS)
	{
		h_intercept(m, ray_angle);
		v_intercept(m, ray_angle);
		m->r->is_it_verticale = 0;
		get_distance(m);
		text_initttt(m, ray_angle);
		renderwalls(m, ray_angle);
		walls(m, count);
		ray_angle += m->fov_angle / NUM_RAYS;
		ray_angle = normalize_angle(ray_angle);
		count++;
	}
}

unsigned int	ft_get_pixel(t_text *m, int x, int y)
{
	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return (0);
	return (m->addr[SCALE * y + x]);
}

void	walls(t_my_struct *m, int count)
{
	int	x;
	int	y;
	int	distfromtop;

	y = 0;
	m->r->top_of_wall = (HEIGHT / 2) - (m->r->wallstripeheight / 2);
	m->r->index = m->r->top_of_wall;
	if (m->r->top_of_wall < 0)
		m->r->top_of_wall = 0;
	m->r->end_of_wall = (HEIGHT / 2) + (m->r->wallstripeheight / 2);
	if (m->r->end_of_wall > HEIGHT)
		m->r->end_of_wall = HEIGHT;
	if (m->r->is_it_verticale)
		x = (int)m->r->vwally % SCALE;
	else
		x = (int)m->r->howallx % SCALE;
	while (m->r->index < m->r->end_of_wall)
	{
		distfromtop = m->r->index + (m->r->wallstripeheight / 2) - (HEIGHT / 2);
		y = distfromtop * ((double)SCALE / m->r->wallstripeheight);
		ft_put_pixel(m, count, m->r->index, ft_get_pixel(&m->t, x, y));
		m->r->index++;
	}
}

void	renderwalls(t_my_struct *m, double ray_angle)
{
	double	disprojectionplane;
	double	correctwalldist;

	correctwalldist = (float)(m->r->final_distance) * cos(ray_angle \
	- m->rot_angle);
	disprojectionplane = (WIDTH / 2) / tan(m->fov_angle / 2);
	m->r->wallstrip = 0.3 * ((SCALE / correctwalldist) * disprojectionplane);
	m->r->wallstripeheight = m->r->wallstrip;
}
