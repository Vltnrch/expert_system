/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multi_rules.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 14:14:15 by vroche            #+#    #+#             */
/*   Updated: 2015/06/11 14:24:40 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

static int		ft_check_no_multi_rules_part1(t_env *env, t_list *lrules)
{
	t_list		*lrules2;
	t_rules		*rule;
	t_rules		*rule2;
	float		len;

	while (lrules)
	{
		rule = lrules->content;
		len = add_ascii(rule->before);
		lrules2 = env->lrules;
		while (lrules2)
		{
			rule2 = lrules2->content;
			if (len == add_ascii(rule2->before))
			{
				if ((rule != rule2) \
					&& ((add_ascii(rule->after) == add_ascii(rule2->after)) \
					|| ft_check_char(rule->after, rule2->after) == 0))
					return (0);
			}
			lrules2 = lrules2->next;
		}
		lrules = lrules->next;
	}
	return (1);
}

static int		ft_check_no_multi_rules_part2(t_env *env, t_list *lrules)
{
	t_list		*lrules2;
	t_rules		*rule;
	t_rules		*rule2;
	float		len;

	while (lrules)
	{
		rule = lrules->content;
		len = add_ascii(rule->after);
		lrules2 = env->lrules;
		while (lrules2)
		{
			rule2 = lrules2->content;
			if (len == add_ascii(rule2->after))
			{
				if ((rule != rule2) \
					&& (add_ascii(rule->before) == add_ascii(rule2->before)))
					return (0);
			}
			lrules2 = lrules2->next;
		}
		lrules = lrules->next;
	}
	return (1);
}

int				ft_check_no_multi_rules(t_env *env)
{
	t_list		*lrules;

	lrules = env->lrules;
	if (ft_check_no_multi_rules_part1(env, lrules) == 0)
		return (0);
	if (ft_check_no_multi_rules_part2(env, lrules) == 0)
		return (0);
	return (1);
}
