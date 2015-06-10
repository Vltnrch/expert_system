/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 12:13:03 by vroche            #+#    #+#             */
/*   Updated: 2015/06/10 17:30:34 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

void	ft_add_rules(t_env *env, char *before, char *after)
{
	t_rules	newrule;
	t_list	*newlink;

	newrule.before = before;
	newrule.after = after;
	newlink = ft_lstnew((void *)&newrule, sizeof(t_rules));
	ft_lstadd_back(&(env->lrules), newlink);
}

void	ft_add_facts(t_env *env, char name, int status)
{
	t_facts	newfact;
	t_list	*newlink;

	if (ft_fact_isexist(env, name))
		return ;
	newfact.name = name;
	newfact.status = status;
	newfact.insearch = 0;
	newlink = ft_lstnew((void *)&newfact, sizeof(t_facts));
	ft_lstadd_back(&(env->lfacts), newlink);
}

int		ft_fact_isexist(t_env *env, char name)
{
	t_list	*lfacts;
	t_facts *fact;

	lfacts = env->lfacts;
	while (lfacts)
	{
		fact = lfacts->content;
		if (fact->name == name)
			return (1);
		lfacts = lfacts->next;
	}
	return (0);
}

int		ft_fact_isinsearch(t_env *env, char name)
{
	t_list	*lfacts;
	t_facts *fact;

	lfacts = env->lfacts;
	while (lfacts)
	{
		fact = lfacts->content;
		if (fact->name == name)
		{
			if (fact->insearch == 1)
				return (1);
			else
				return (0);
		}
		lfacts = lfacts->next;
	}
	return (0);
}

int		ft_getstatus_fact(t_env *env, char name)
{
	t_list	*lfacts;
	t_facts *fact;

	lfacts = env->lfacts;
	while (lfacts)
	{
		fact = lfacts->content;
		if (fact->name == name)
			return (fact->status);
		lfacts = lfacts->next;
	}
	return (UNDETER);
}

void	ft_changestatus_fact(t_env *env, char name, int status)
{
	t_list	*lfacts;
	t_facts *fact;

	lfacts = env->lfacts;
	while (lfacts)
	{
		fact = lfacts->content;
		if (fact->name == name)
			fact->status = status;
		lfacts = lfacts->next;
	}
}

void	ft_changeinsearch_fact(t_env *env, char name, int insearch)
{
	t_list	*lfacts;
	t_facts *fact;

	lfacts = env->lfacts;
	while (lfacts)
	{
		fact = lfacts->content;
		if (fact->name == name)
			fact->insearch = insearch;
		lfacts = lfacts->next;
	}
}
