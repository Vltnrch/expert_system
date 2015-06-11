/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 12:27:14 by vroche            #+#    #+#             */
/*   Updated: 2015/06/11 12:27:32 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

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
