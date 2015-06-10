/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 15:10:56 by hleber            #+#    #+#             */
/*   Updated: 2015/06/09 18:43:08 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

int valid_rules(t_expsys *exsy)
{
	int i;

	i = 0;
	if (exsy->str[i] == '?' || exsy->str[i] == '=')
	{
		if (check_facts(exsy, i) == 0)
			return (0);
	}
	else
	{
		while (exsy->str[i])
		{
			
			if (exsy->str[i] == '|' || exsy->str[i] == '^' || exsy->str[i] == '+')
			{
				if (check_operand(exsy, i) == 0)
					return (0);
			}
			else if (exsy->str[i] == '>')
			{
				if (check_imp(exsy, i) == 0)
					return (0);
				return (1);
			}
			else if (valid_rules2(exsy, i) == 0)
				return (0);
			i++;
		}
	}
	return (1);
}

int valid_rules2(t_expsys *exsy, int i)
{
	if (exsy->str[i] == '!')
		if (check_point(exsy, i) == 0)
			return (0);
	if (exsy->str[i] >= 'A' && exsy->str[i] <= 'Z')
		if (check_operator(exsy, i) == 0)
			return (0);
	if (exsy->str[i] == '=')
		if (check_equal(exsy, i) == 0)
			return (0);
	if (exsy->str[i] == '(' || exsy->str[i] == ')')
		if (check_bracket(exsy, i) == 0)
			return (0);
	return (1);
}
