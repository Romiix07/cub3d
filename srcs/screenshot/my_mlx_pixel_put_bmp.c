/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put_bmp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:41:53 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/29 14:47:19 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	my_mlx_pixel_put_bmp(int fd, unsigned int color)
{
	write(fd, &color, sizeof(char) * 3);
}
