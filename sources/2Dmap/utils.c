/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:05:37 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/25 19:38:46 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalize_angle(double angl)
{
	double	angle;

	angle = fmod(angl, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

int	check_up_down(double angle)
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

int	check_left_right(double angle)
{
	if (angle < M_PI_2 || angle > 1.5 * M_PI)
		return (1);
	return (0);
}

int	find_wall(double x, double y, t_my_struct *m)
{
	if (x < 0 || (int)x >= m->map_width || y < 0 || (int)y >= m->map_height)
		return (1);
	if (m->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

double	distance_of_two_points(t_my_struct *m, double d1, double d2)
{
	double	x;
	double	y;
	double	angle;

	x = m->player_x * SCALE;
	y = m->player_y * SCALE;
	angle = m->rot_angle;
	return ((d1 - x) * cos(angle) + (d2 - y) * sin(angle));
}
