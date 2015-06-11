/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:46:25 by vroche            #+#    #+#             */
/*   Updated: 2015/06/11 14:00:41 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

static void ft_calc_rule_left_dl(t_env *env, t_calc *calc, t_calc *work)
{
	if (*(calc->calcul) == '!')
	{
		calc->reverse = 1;
		(calc->calcul)++;
	}
	if (*(calc->calcul) == '(')
	{
		work->calcul = calc->calcul + 1;
		work->left_dl = NULL;
		work->op_dl = NULL;
		work->prio_op_pre = 0;
		work->p_calcul = &(calc->calcul);
		calc->left = ft_calc_rule(env, work);
	}
	else
	{
		calc->left = ft_engine(env, *(calc->calcul));
		(calc->calcul)++;
	}
	if (calc->reverse == 1)
	{
		if (calc->left != UNDETER)
			calc->left = !calc->left;
		calc->reverse = 0;
	}
}

static void ft_calc_rule_while1(t_env *env, t_calc *calc, t_calc *work)
{
	if (*(calc->calcul) == '!')
	{
		calc->reverse = 1;
		calc->calcul++;
	}
	if (*(calc->calcul) == '(')
	{
		work->calcul = calc->calcul + 1;
		work->left_dl = NULL;
		work->op_dl = NULL;
		work->prio_op_pre = 0;
		work->p_calcul = &(calc->calcul);
		calc->right = ft_calc_rule(env, work);
	}
	else
	{
		calc->right = ft_engine(env, *(calc->calcul));
		(calc->calcul)++;
	}
	if (calc->reverse == 1)
	{
		if (calc->right != UNDETER)
			calc->right = !calc->right;
		calc->reverse = 0;
	}
}

static void ft_calc_rule_while2(t_env *env, t_calc *calc, t_calc *work)
{
	calc->op_next = *(calc->calcul);
	(calc->calcul)++;
	if (ft_isop(calc->op_next) && \
		ft_priority_op(calc->op_next) > ft_priority_op(calc->op))
	{
		work->calcul = calc->calcul;
		work->left_dl = &(calc->right);
		work->op_dl = &(calc->op_next);
		work->prio_op_pre = ft_priority_op(calc->op);
		work->p_calcul = &(calc->calcul);
		calc->right = ft_calc_rule(env, work);
	}
	calc->left = ft_do_op(calc->left, calc->op, calc->right);
	calc->op = calc->op_next;
}

static void ft_calc_rule_finish(t_calc *calc)
{
	if (calc->op_dl != NULL)
		*(calc->op_dl) = calc->op_next;
	if (calc->p_calcul != NULL)
		*(calc->p_calcul) = calc->calcul;
}

int			ft_calc_rule(t_env *env, t_calc *calc)
{
	t_calc	*work;

	calc->reverse = 0;
	work = (t_calc *)malloc(sizeof(t_calc));
	if (calc->left_dl != NULL)
		calc->left = *(calc->left_dl);
	else
		ft_calc_rule_left_dl(env, calc, work);
	if (calc->op_dl != NULL)
		calc->op = *(calc->op_dl);
	else
	{
		calc->op = *(calc->calcul);
		(calc->calcul)++;
	}
	while (calc->op != '\0' && calc->op != ')' && \
		ft_priority_op(calc->op) > calc->prio_op_pre)
	{
		ft_calc_rule_while1(env, calc, work);
		ft_calc_rule_while2(env, calc, work);
	}
	ft_calc_rule_finish(calc);
	free(work);
	return (calc->left);
}
