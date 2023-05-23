/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:50:07 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/23 22:50:51 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rander(t_my_struct *m)
{
	int		count;
	double	ray_angle;

	count = 0;
	ray_angle = m->r->rayangle - (FOV_ANGLE / 2);
	ray_angle = normalize_angle(ray_angle);

	text_init(m);
	while (count < NUM_RAYS)
	{
		h_intercept(m, ray_angle);
		v_intercept(m, ray_angle);
		get_distance(m);
		renderwalls(m, ray_angle);
		walls(m, count);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		ray_angle = normalize_angle(ray_angle);
		count++;
	}
}
void text_init(t_my_struct *m)
{
	char *path;
	int i;
	int j;
	m->t.bpp = 0;
	m->t.line_length = 0;
	m->t.endian = 0;
	path = "textures/omi.xpm";
	m->t.img = mlx_xpm_file_to_image(m->mlx_ptr, path, &i, &j);
	m->t.addr = mlx_get_data_addr(m->t.img, &m->t.bpp, &m->t.line_length, &m->t.endian);
}

unsigned int	ft_get_pixel(t_text m, int x, int y)
{
	int		offset;
	char	*dst;

	(void)dst;
	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return 0;
	offset = (y * m.line_length) + (x * m.bpp/8);
	unsigned int a = *((unsigned int *)(m.addr + offset));
	//printf("*****%d, %d, %d\n", m.line_length, m.bpp, offset);
	return(a);
}

void	walls(t_my_struct *m, int count)
{
	int	top_of_wall;
	int end_of_wall;
	int x;
	int y = 0;
	float temp;
	int window_x;
	int	save;

	(void)count;
	top_of_wall = (HEIGHT / 2) - (m->r->wallstrip / 2);
	end_of_wall = (HEIGHT / 2) + (m->r->wallstrip / 2);
	float height_wall = end_of_wall - top_of_wall;
	save = top_of_wall;
	if(top_of_wall < 0)
		top_of_wall = 0;
	if(height_wall > HEIGHT)
		height_wall = HEIGHT;

	/*if(m->r->hflag)
		x = ((int)m->r->wallhitx % SCALE);
	else if(m->r->vflag)
		x = ((int)m->r->wallhity % SCALE);*/
	if(m->r->hflag)
	{
		x = m->r->wallhitx * SCALE;
		window_x = m->r->wallhitx * WIDTH;
	}
	else if(m->r->vflag)
	{
		x = m->r->wallhity * SCALE;
		window_x = m->r->wallhity * WIDTH;
	}
	while (top_of_wall < end_of_wall)
	{
		temp = top_of_wall - save;
		//temp = (f)(top_of_wall - save) / height_wall;
		y = (temp / height_wall) * SCALE;
		//printf("%f\n", y);
		int color = ft_get_pixel(m->t, x + count, y);
		ft_put_pixel(m, window_x + count, top_of_wall, color);
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
	m->r->wallstrip = (SCALE / correctwalldist) * disprojectionplane;
	m->r->wallstrip *= 0.3;
}
