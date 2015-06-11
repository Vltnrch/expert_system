/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 18:44:07 by hleber            #+#    #+#             */
/*   Updated: 2015/06/11 12:37:42 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

int check_operator(t_expsys *exsy, int i)
{
	if (i >= 1 && exsy->str[i - 1] != '+' &&
	exsy->str[i - 1] != '^' && exsy->str[i - 1] != '|' &&
	exsy->str[i - 1] != '(' && exsy->str[i - 1] != '!' &&
	exsy->str[i - 1] != '?' && exsy->str[i - 1] >= 'A' &&
	exsy->str[i - 1] <= 'Z')
		return (0);
	else if (exsy->str[i + 1] != '+' && exsy->str[i + 1] != '^' &&
	exsy->str[i + 1] != '|' && exsy->str[i + 1] != ')' &&
	exsy->str[i + 1] != '\0' &&
	exsy->str[i + 1] != '=')
		return (0);
	else
		return (1);
}

int check_operand(t_expsys *exsy, int i)
{
	if ((exsy->str[i - 1] < 'A' || exsy->str[i - 1] > 'Z') &&
	exsy->str[i - 1] != ')' && i >= 1)
		return (0);
	else if ((exsy->str[i + 1] < 'A' || exsy->str[i + 1] > 'Z')
	&& exsy->str[i + 1] != '(' && exsy->str[i + 1] != '!')
		return (0);
	else
		return (1);
}

int check_equal(t_expsys *exsy, int i)
{
	if ((exsy->str[i - 1] < 'A' || exsy->str[i - 1] > 'Z') &&
	exsy->str[i - 1] != ')' && i >= 1)
		return (0);
	else if (exsy->str[i + 1] != '>')
		return (0);
	else
		return (1);
}

int check_imp(t_expsys *exsy, int i)
{
	if (i >= 1 && exsy->str[i++ - 1] != '=')
		return (0);
	else
	{
		while (exsy->str[i])
		{
			if ((exsy->str[i] < 'A' || exsy->str[i] > 'Z') &&
				exsy->str[i] != '!' && exsy->str[i] != '+')
				return (0);
			else if (exsy->str[i] == '!')
			{
				if (check_point(exsy, i) == 0)
					return (0);
			}
			else if (exsy->str[i] >= 'A' && exsy->str[i] <= 'Z')
			{
				if (check_operator(exsy, i) == 0)
					return (0);
			}
			else if (check_operand(exsy, i) == 0)
				return (0);
			i++;
		}
	}
	return (1);
}

int check_bracket(t_expsys *exsy, int i)
{
	if (exsy->str[i] == '(' && exsy->str[i - 1] != '(' &&
	exsy->str[i - 1] == '+' && exsy->str[i - 1] == '|' &&
	exsy->str[i - 1] == '^' && i >= 1)
		return (0);
	else if (exsy->str[i] == ')' && exsy->str[i + 1] != ')' &&
	exsy->str[i + 1] != '=' && exsy->str[i + 1] == '+' &&
	exsy->str[i + 1] == '|' && exsy->str[i + 1] == '^')
		return (0);
	else
		return (1);
}
