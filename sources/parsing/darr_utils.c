/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:12:03 by bkamal            #+#    #+#             */
/*   Updated: 2023/05/23 02:12:41 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_darr(char **darr)
{
	size_t	i;

	i = 0;
	while (darr[i])
	{
		free(darr[i]);
		i++;
	}
	free(darr);
}

int	len_darr(char **darr)
{
	int	i;

	i = -1;
	while (darr[++i])
		;
	return (i);
}