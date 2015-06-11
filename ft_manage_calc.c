/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:48:45 by vroche            #+#    #+#             */
/*   Updated: 2015/06/11 14:42:27 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

int	ft_do_op(int left, char op, int right)
{
	if (left == UNDETER || right == UNDETER)
	{
		if (op == '+' && (left == FALSE || right == FALSE))
			return (FALSE);
		else if (op == '|' && (left == TRUE || right == TRUE))
			return (TRUE);
		return (UNDETER);
	}
	else if (op == '+')
		return (left & right);
	else if (op == '|')
		return (left | right);
	else if (op == '^')
		return (left ^ right);
	return (UNDETER);
}

int	ft_priority_op(char op)
{
	if (op == '+')
		return (3);
	if (op == '|')
		return (2);
	if (op == '^')
		return (1);
	return (0);
}

int	ft_isop(char op)
{
	if (op == '+' || op == '|' || op == '^')
		return (1);
	return (0);
}
