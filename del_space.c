/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 18:57:31 by hleber            #+#    #+#             */
/*   Updated: 2015/06/11 12:45:38 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

static void del_isspace_comment(t_expsys *exsy, int i)
{
	while (exsy->str[i])
	{
		exsy->str[i] = 0;
		i++;
	}
}

void		del_isspace(t_expsys *exsy)
{
	int i;
	int p;

	i = 0;
	while (exsy->str[i])
	{
		if (ft_isspace(exsy->str[i]) > 0)
		{
			p = i;
			while (exsy->str[p])
			{
				exsy->str[p] = exsy->str[p + 1];
				p++;
			}
			i--;
		}
		else if (exsy->str[i] == '#')
			return (del_isspace_comment(exsy, i));
		i++;
	}
}
