/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:15:00 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/23 11:27:08 by hcharef          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_struct_init(t_my_struct *data)
{
	data->imge.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->imge.addr = mlx_get_data_addr(data->imge.img, \
	&data->imge.bpp, &data->imge.line_length, &data->imge.endian);
}

void	ft_put_pixel(t_my_struct *data, int x, int y, int color)
{
	int		offset;
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * data->imge.line_length) + (x * (data->imge.bpp / 8));
	dst = data->imge.addr + offset;
	*(unsigned int *)dst = color;
}

void	draw_square(t_my_struct *m, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			ft_put_pixel(m, x + j, y, 0xFFFFFF);
			ft_put_pixel(m, x + j, y + i, 56545);
			j++;
		}
		ft_put_pixel(m, x, y + i, 5654565);
		i++;
	}
}

void	draw_back(t_my_struct *m, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			ft_put_pixel(m, x + j, y, 564889);
			ft_put_pixel(m, x + j, y + i, 7898);
			j++;
		}
		ft_put_pixel(m, x, y + i, 0x000000);
		i++;
	}
}

void iterater(t_my_struct *m)
{
	int count;
	int count2;

	count = 0;
	while(count < m->map_height * SCALE)
	{
		count2 = 0;
		while(count2 < m->map_width * SCALE)
		{
			
			if(m->map[count / SCALE][count2 / SCALE] == '1')
				draw_square(m, count2, count);
			else
				draw_back(m, count2, count);
			count2 += SCALE;
		}
		count += SCALE;
	}
	player(m, m->player_x, m->player_y);
}

void	draw(t_my_struct *m)
{
	int	x;
	int	y;

	x = 0;
	while (x < HEIGHT / 2)
	{
		y = 0;
		while (y < WIDTH)
		{
			ft_put_pixel(m, y, x, 0x008bec);
			y++;
		}
		x++;
	}
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			ft_put_pixel(m, y, x, 0x353422);
			y++;
		}
		x++;
	}
}
