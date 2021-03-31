/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 02:15:47 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/31 02:15:47 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	char	*str;
	int		r;
	int		end;
}				t_list;

int				get_next_line(int fd, char **line);
int				ch_n(char *str);
char			*str_edit(char *str, int end);
#endif
