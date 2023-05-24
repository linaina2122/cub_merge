/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:04:32 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/23 15:00:42 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	player_orientation(char player_start)
{
	if (player_start == 'N')
		return (M_PI * 1.5);
	else if (player_start == 'S')
		return (M_PI * 0.5);
	else if (player_start == 'W')
		return (M_PI);
	return (0.0);
}