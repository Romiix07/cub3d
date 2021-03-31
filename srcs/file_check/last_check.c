/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <cmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:09:56 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/31 16:04:09 by cmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	last_check(t_cub *cub)
{
	if (cub->north == NULL || cub->south == NULL || cub->east == NULL || cub->
	west == NULL || cub->sprite == NULL)
		return (error_code('T'));
	if (cub->start == 0)
		return (error_code('M'));
	if (cub->floor_color == -1)
		return (error_code('F'));
	if (cub->ceiling_color == -1)
		return (error_code('C'));
	if (cub->res_x == -1 || cub->res_y == -1)
		return (error_code('R'));
	return (1);
}
