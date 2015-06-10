/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hleber <hleber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 15:09:53 by hleber            #+#    #+#             */
/*   Updated: 2015/06/08 15:10:34 by hleber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

int valid_file(t_expsys *exsy)
{
	int i;

	i = 0;
	while (exsy->str[i])
	{
		if ((exsy->str[i] < 'A' || exsy->str[i] > 'Z') && exsy->str[i] !=
		'(' && exsy->str[i] != '!' &&
		exsy->str[i] != '=' && exsy->str[i] != '?' && exsy->str[i] != '\0' &&
		exsy->str[i] != ')' && exsy->str[i] != '>' && exsy->str[i] != '|' &&
		exsy->str[i] != '+' && exsy->str[i] != '^')
			return (0);
		i++;
	}
	return (1);
}
