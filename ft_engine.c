/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 17:21:40 by vroche            #+#    #+#             */
/*   Updated: 2015/06/11 18:13:01 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

static int	ft_engine_part2(t_env *env, char *calcr, \
							t_rules *rule, t_calc *work)
{
	int		status;
	int		reverse;

	reverse = 0;
	if (calcr != rule->after && *(calcr - 1) == '!')
		reverse = 1;
	calcr = rule->before;
	work->calcul = calcr;
	work->left_dl = NULL;
	work->op_dl = NULL;
	work->prio_op_pre = 0;
	work->p_calcul = NULL;
	status = ft_calc_rule(env, work);
	if (status != UNDETER)
	{
		if (reverse == 1)
			status = !status;
		return (status);
	}
	return (-1);
}

static int	ft_engine_part(t_env *env, char name)
{
	int		rtn;
	t_list	*lrules;
	char	*calc_rule;
	t_calc	work;

	lrules = env->lrules;
	while (lrules)
	{
		if ((calc_rule = \
			ft_strchr(((t_rules *)(lrules->content))->after, name)))
		{
			if ((rtn = ft_engine_part2(env, calc_rule, \
									lrules->content, &work)) != -1)
			{
				ft_changestatus_fact(env, name, rtn);
				return (rtn);
			}
		}
		lrules = lrules->next;
	}
	return (-1);
}

int			ft_engine(t_env *env, char name)
{
	int		status;
	int		rtn;

	if (ft_fact_isinsearch(env, name))
	{
		return (UNDETER);
	}
	if ((status = ft_getstatus_fact(env, name)) != DETER)
	{
		return (status);
	}
	ft_changeinsearch_fact(env, name, 1);
	if ((rtn = ft_engine_part(env, name)) != -1)
	{
		ft_changeinsearch_fact(env, name, 0);
		return (rtn);
	}
	ft_changeinsearch_fact(env, name, 0);
	return (UNDETER);
}

static void	ft_display_question(t_env *env, int result, \
							char question, int reverse)
{
	if (reverse == 1)
		ft_printf("\033[1;34;40m!\033[0m");
	ft_printf("\033[1;34;40m%c\033[0m is ", question);
	if (result == FALSE)
	{
		if (env->finish != UNDETER)
			env->finish = FALSE;
		ft_printf("\033[1;31;40mFalse\033[0m\n");
	}
	else if (result == TRUE)
		ft_printf("\033[1;32;40mTrue\033[0m\n");
	else if (result == UNDETER)
	{
		env->finish = UNDETER;
		ft_printf("\033[1;37;41mUndeterminable\033[0m\n");
	}
}

void		ft_backward_chaining(t_env *env)
{
	int		result;
	char	*questions;
	int		reverse;

	result = TRUE;
	questions = env->questions;
	while (*questions && (result = TRUE))
	{
		reverse = 0;
		if (*questions == '!')
		{
			reverse = 1;
			questions++;
		}
		result = ft_engine(env, *questions);
		if (reverse == 1 && result != UNDETER)
			result = !result;
		ft_display_question(env, result, *questions, reverse);
		questions++;
	}
}
