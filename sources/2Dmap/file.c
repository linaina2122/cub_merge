/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:41:24 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/24 14:55:07 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player(t_my_struct *m, double x, double y)
{
	int i;
	int j;
	double count;
	double count2;
	count = x * SCALE;
	count2 = y * SCALE; 
	i = -5; 
	while(i < 5 )
	{ 
		j = -5;
		while(j < 5)
		{
			ft_put_pixel(m, count + j, count2 + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

int mouvements_press(int keycode, t_my_struct *m)
{
	if (keycode == 13)
		m->move[0] = 1;
	if (keycode == 1)
		m->move[0] = 2;

	if(keycode == 0)
		m->move[1] = 1;
	if (keycode == 2)
		m->move[1] = 2;

	if(keycode == 124)
		m->move[2] = 1;
	if( keycode == 123)
		m->move[2] = 2;
		
	if (keycode == 53)
		exit(1);
	return(keycode);
}

int mouvements_release(int keycode, t_my_struct *m)
{
	if(keycode == 13 || keycode == 1)
		m->move[0] = 0;
	if(keycode == 0 || keycode == 2)
		m->move[1] = 0;
	if(keycode == 124 || keycode == 123)
		m->move[2] = 0;
	if (keycode == 53)
		exit(1);
	return(keycode);
}
