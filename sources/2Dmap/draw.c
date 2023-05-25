/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharef <hcharef@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:15:00 by hcharef           #+#    #+#             */
/*   Updated: 2023/05/25 19:34:49 by hcharef          ###   ########.fr       */
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

void	draw(t_my_struct *m)
{
	double	x;
	double	y;

	x = 0;
	while (x < HEIGHT / 2)
	{
		y = 0;
		while (y < WIDTH)
		{
			ft_put_pixel(m, y, x, m->ceil_col);
			y++;
		}
		x++;
	}
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			ft_put_pixel(m, y, x, m->floor_col);
			y++;
		}
		x++;
	}
}
