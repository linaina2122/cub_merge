/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:29:03 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/25 19:50:48 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_up(t_my_struct *m)
{
	double	new_y;
	double	new_x;

	m->var = 0.8 * m->speed;
	new_y = m->player_y + sin(m->rot_angle) * m->var;
	new_x = m->player_x + cos(m->rot_angle) * m->var;
	if (m->map[(int)(new_y - 0.2)][(int)(new_x - 0.2)] == '1' ||
		m->map[(int)(new_y + 0.2)][(int)(new_x + 0.2)] == '1' || \
		m->map[(int)(new_y - 0.2)][(int)(m->player_x - 0.2)] == '1' || \
			m->map[(int)(m->player_y + 0.2)][(int)(new_x + 0.2)] == '1')
		return (1);
	m->player_y += sin(m->rot_angle) * m->var;
	m->player_x += cos(m->rot_angle) * m->var;
	return (0);
}

int	move_down(t_my_struct *m)
{
	double	new_y;
	double	new_x;

	m->var = 0.8 * m->speed;
	new_y = m->player_y - sin(m->rot_angle) * m->var;
	new_x = m->player_x - cos(m->rot_angle) * m->var;
	if (m->map[(int)(new_y + 0.2)][(int)(new_x + 0.2)] == '1' ||
		m->map[(int)(new_y - 0.2)][(int)(new_x - 0.2)] == '1' ||
		m->map[(int)(new_y - 0.2)][(int)(m->player_x - 0.2)] == '1' || \
		m->map[(int)(m->player_y + 0.2)][(int)(new_x + 0.2)] == '1')
		return (1);
	m->player_y -= sin(m->rot_angle) * m->var;
	m->player_x -= cos(m->rot_angle) * m->var;
	return (0);
}

int	right_move(t_my_struct *m)
{
	double	new_y;
	double	new_x;
	double	new_rot;

	m->var = 0.8 * m->speed;
	new_y = m->player_y + sin(m->rot_angle) * m->var;
	new_x = m->player_x + cos(m->rot_angle) * m->var;
	if (m->map[(int)(new_y - 0.2)][(int)(new_x - 0.2)] == '1' ||
		m->map[(int)(new_y + 0.2)][(int)(new_x + 0.2)] == '1' || \
		m->map[(int)(new_y - 0.2)][(int)(m->player_x - 0.2)] == '1' || \
		m->map[(int)(m->player_y + 0.2)][(int)(new_x + 0.2)] == '1')
		return (1);
	new_rot = m->rot_angle - M_PI_2;
	m->player_y += sin(new_rot) * m->var;
	m->player_x += cos(new_rot) * m->var;
	return (0);
}

int	left_move(t_my_struct *m)
{
	double	new_y;
	double	new_x;
	double	new_rot;

	m->var = 0.8 * m->speed;
	new_y = m->player_y + sin(m->rot_angle) * m->var;
	new_x = m->player_x + cos(m->rot_angle) * m->var;
	if (m->map[(int)(new_y - 0.2)][(int)(new_x - 0.2)] == '1' ||
		m->map[(int)(new_y + 0.2)][(int)(new_x + 0.2)] == '1' ||
		m->map[(int)(new_y - 0.2)][(int)(m->player_x - 0.2)] == '1' || \
			m->map[(int)(m->player_y + 0.2)][(int)(new_x + 0.2)] == '1')
		return (1);
	new_rot = m->rot_angle - M_PI_2;
	m->player_y -= sin(new_rot) * m->var;
	m->player_x -= cos(new_rot) * m->var;
	return (0);
}
