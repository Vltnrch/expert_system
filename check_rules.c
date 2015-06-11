/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 15:10:56 by hleber            #+#    #+#             */
/*   Updated: 2015/06/11 16:37:52 by hleber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

static int	valid_rules_part(t_expsys *exsy, int i)
{
	int flag;

	flag = 0;
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
		if (exsy->str[i] == '=')
			flag = 1;
		i++;
	}
	return (flag);
}

int			valid_rules(t_expsys *exsy)
{
	int	i;

	i = 0;
	if (exsy->str[i] == '?' || exsy->str[i] == '=')
	{
		if (check_facts(exsy, i) == 0)
			return (0);
	}
	else if (exsy->str[i] == 0)
		return (1);
	else
	{
		if (valid_rules_part(exsy, i) == 0)
			return (0);
	}
	return (1);
}

int			valid_rules2(t_expsys *exsy, int i)
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
