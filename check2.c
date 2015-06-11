/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/06 18:46:12 by hleber            #+#    #+#             */
/*   Updated: 2015/06/11 17:50:30 by hleber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

int			check_par(t_expsys *exsy)
{
	int flag;
	int i;

	i = 0;
	flag = 0;
	while (exsy->str[i])
	{
		if (exsy->str[i] == ')')
			flag--;
		if (exsy->str[i] == '(')
			flag++;
		i++;
	}
	return (flag);
}

static int	check_question(t_expsys *exsy, int i)
{
	if (exsy->str[i] == '?')
	{
		i += 1;
		while (exsy->str[i])
		{
			if ((exsy->str[i] < 'A' || exsy->str[i] > 'Z') \
				&& exsy->str[i] != '!')
				return (0);
			else if (exsy->str[i] == '!')
			{
				if (exsy->str[i + 1] < 'A' || exsy->str[i + 1] > 'Z')
					return (0);
			}
			i++;
		}
	}
	return (1);
}

int			check_facts(t_expsys *exsy, int i)
{
	if (exsy->str[i] == '=')
	{
		i += 1;
		while (exsy->str[i])
		{
			if ((exsy->str[i] < 'A' || exsy->str[i] > 'Z') &&
			exsy->str[i] != '!')
				return (0);
			i++;
		}
	}
	if (exsy->str[i] == '?')
	{
		if (check_question(exsy, i) == 0)
			return (0);
	}
	return (1);
}

int			check_point(t_expsys *exsy, int i)
{
	if (exsy->str[i - 1] != '+' && exsy->str[i - 1] != '^' \
		&& exsy->str[i - 1] != '|' && exsy->str[i - 1] != '>' \
		&& exsy->str[i - 1] != '(' && i >= 1)
		return (0);
	else if ((exsy->str[i + 1] < 'A' || exsy->str[i + 1] > 'Z') \
				&& exsy->str[i + 1] != '(')
		return (0);
	return (1);
}

int			valid_file(t_expsys *exsy)
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
