/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memdel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:41:19 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/31 00:51:24 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "cub3d.h"

int	ft_memdel(char **s, int fd)
{
	if (fd > 0)
		close(fd);
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (0);
}
