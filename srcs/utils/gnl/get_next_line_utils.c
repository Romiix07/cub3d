/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 00:50:56 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/31 00:50:56 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ch_n(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '\n')
			j++;
	return (j);
}

char	*str_edit(char *str, int end)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (end == 0)
	{
		free(str);
		str = NULL;
		return (str);
	}
	while (str[i] && str[i] != '\n')
		i++;
	while (str[i++])
		str[j++] = str[i];
	str[j] = '\0';
	return (str);
}
