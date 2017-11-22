/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 14:03:21 by vroche            #+#    #+#             */
/*   Updated: 2015/06/11 17:53:58 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

void		ft_cut_rules(t_env *env, t_expsys *exsy)
{
	int		len;
	char	*tmp;
	char	*before;
	char	*after;

	len = 0;
	tmp = exsy->str;
	while (*tmp && *tmp++ != '=')
		len++;
	before = ft_strnew(len);
	before = ft_strncpy(before, exsy->str, len);
	exsy->str += len + 2;
	tmp = exsy->str;
	while (*tmp++)
		len++;
	after = ft_strnew(len);
	after = ft_strncpy(after, exsy->str, len);
	ft_add_rules(env, before, after);
}

static void	ft_createlist_facts_part(t_env *env, t_rules *rules)
{
	char		*tmp;

	tmp = rules->before;
	while (*tmp)
	{
		if (*tmp >= 'A' && *tmp <= 'Z')
			ft_add_facts(env, *tmp, UNDETER);
		tmp++;
	}
	tmp = rules->after;
	while (*tmp)
	{
		if (*tmp >= 'A' && *tmp <= 'Z')
		{
			ft_add_facts(env, *tmp, DETER);
			if (ft_fact_isexist(env, *tmp))
				ft_changestatus_fact(env, *tmp, DETER);
		}
		tmp++;
	}
}

void		ft_createlist_facts(t_env *env)
{
	t_rules		*rules;
	t_list		*lrules;

	lrules = env->lrules;
	while (lrules != NULL)
	{
		rules = lrules->content;
		ft_createlist_facts_part(env, rules);
		lrules = lrules->next;
	}
}

void		ft_init_facts(t_env *env)
{
	char	*tmp;
	int		reverse;

	tmp = env->initfacts;
	reverse = 0;
	while (*tmp)
	{
		if (*tmp == '!')
		{
			tmp++;
			reverse = 1;
		}
		if (*tmp >= 'A' && *tmp <= 'Z')
		{
			if (ft_fact_isexist(env, *tmp))
				ft_changestatus_fact(env, *tmp, (reverse == 1) ? FALSE : TRUE);
			else
				ft_add_facts(env, *tmp, (reverse == 1) ? FALSE : TRUE);
		}
		reverse = 0;
		tmp++;
	}
}

void		ft_perror_exit(const char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" Error", 2);
	exit(EXIT_FAILURE);
}
